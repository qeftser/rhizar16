
#ifndef __RHIZAR16_WIRED_SERV__

#define __RHIZAR16_WIRED_SERV__
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <chrono>

#define __RHIZAR16_WIRED_SERV_INITIAL_CONNECTIONS__ 64 

/* a generalized socket server class that wraps unix and windows
 * system interfaces. Designed for handling consistant reading
 * and writing between the server and several clients. Read and
 * write requests are 'queued', and either succeed or fail as
 * data comes in. This is generally the pattern that I am used
 * to following in my work, so I think it will work well packaged
 * in a class.                                                   */

#ifdef _WIN32

#elif defined(__unix__)

#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <poll.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <arpa/inet.h>

#endif

namespace Rhizar16 {

class WiredServer {
public:

#ifdef _WIN32

#elif defined(__unix__)

   typedef int socktype;

#endif

private:

   const uint verbose;
   std::string verbose_prompt;

   enum ActionState {
      UNKNOWN = 0,
      READING = 1,
      WRITING = 2,
      READY   = 3,
      CLOSED  = 4,
   };

   struct Action {
      uint64_t state = UNKNOWN;
      size_t remaining;
      size_t completed;
      uint8_t * data;
      union {
         struct sockaddr_in  ipv4;
         struct sockaddr_in6 ipv6;
      } addr;
   };

   std::unordered_map<socktype,Action> actions;

   std::thread manager = std::thread();
   std::mutex mux = std::mutex();

   void add_connection(socktype sock);
   void rem_connection(socktype sock);

   void manage();
   
#ifdef _WIN32

#elif defined(__unix__)

   uint connection_len;
   uint connection_pos;
   struct pollfd * connections;
   int listen_ipv4 = 0;
   int listen_ipv6 = 0;

#endif

public:

   WiredServer(uint verbose = 0, std::string verbose_prompt = "WiredServer");
   ~WiredServer();

   /* initialize the listening sockets and other data structures.
    * This can also be called to reset the server if some issues
    * have occured. Return 0 on success and -1 on failure, with errno
    * likely set to the relevant error - but not guaranteed to be :) 
    * 
    * On success, begin accepting incoming connections, processing 
    * queued tasks, and managing exising connections.              
    *
    * Note that an IPv4 connection will be started on the given port, and
    * a */
   int start(uint port);

   /* close down all connections and clean up the server */
   void finish();

   /* place all the ready sockets in the passed vector
    * Note: the vector is not cleared by this function 
    * Return the number of ready sockets              */
   int get_ready(std::vector<socktype> & collection);

   /* same as get_ready, but do not return until at least
    * one socket is ready.                               
    *
    * User can also specify a timeout in nanoseconds that
    * will cause the function to return if time runs out
    * before an open connection is seen                  */
   int wait_ready(std::vector<socktype> & collection, 
                  std::chrono::nanoseconds timeout =
                  std::chrono::nanoseconds::zero());

   /* return in collection all sockets that have been
    * closed by the client or server. These can be 
    * cleaned up by calling the clean method, which
    * will cause them to no longer show up in this list.
    * Return the number of closed sockets.            */
   int get_closed(std::vector<socktype> & collection);

   /* tell the server to write data to the given socket.
    * Return 0 on success, and -1 if the socket
    * is already performing a requested action, i.e. is
    * not ready.                                         
    * Note: the pointer data is held by the server, and will
    * be used as the write is completed. If this value is 
    * freed or modified before the write finishes, it could
    * cause the server to crash.                            */
   int send(socktype socket, uint8_t * data, size_t len);

   /* tell the server to read data to the given socket.
    * Return 0 on success, and -1 if the socket
    * is not in the ready state, i.e. is closed, reading, or
    * writing.
    * Note: the pointer data is held by the server, and will
    * be used as the read is completed. If this value is 
    * freed or modified before the read finishes, it could
    * cause the server to crash.                            */
   int recv(socktype socket, uint8_t * data, size_t len);

   /* close the given socket.
    * Return 0 on success, -1 if the socket is not in the
    * ready state or if an error occurs                   */
   int close(socktype socket);

   /* remove all closed sockets from internal storage, allowing
    * the open slots to be reused. Will return the number of
    * slots opened up, i.e. the number of closed connections cleaned
    * up.                                                            */
   int clean();

   /* Note that it is up to the user to manage the state of 
    * the sockets that exist inside the server. An attempt
    * to write to a new socket can be completed by calling
    * get_ready, noting if any of the returned sockets have
    * not been seen before, and calling send on these. A
    * later call to get_ready that returns the same sockets
    * should notify the user that the writes have finished and
    * some other action can be performed on the sockets. This
    * method of operation allows the server to run asyncronously,
    * performing many reads and writes over nonblocking sockets
    * in parallel while still accepting and closing both ipv4
    * and ipv6 connections. This should hopefully free the user
    * up to just have to worry about the data they are sending 
    * and recieving, as opposed to managing the communication
    * as well. Note that this requires the server to allocate
    * a seperate thread to manage the sockets.                 */

};

}

#endif
