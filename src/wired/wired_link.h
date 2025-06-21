
#ifndef __RHIZAR16_WIRED_LINK__

#define __RHIZAR16_WIRED_LINK__
#include <stdlib.h>
#include <stdint.h>
#include <string>

/* A generalized socket class that wraps unix and windows
 * systems. This will be used to facilitate connections
 * between nodes in parallel systems, allowing computation
 * to be shared across as many devices as possible.      */

#ifdef _WIN32
typedef unsigned int uint;

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <winsock.h>
#include <windows.h>
#include <ws2def.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>

#elif defined(__unix__)

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

#endif

namespace Rhizar16 {

class WiredLink {
private:

   const uint options;
   std::string verbose_prompt;
   bool is_live;

#ifdef _WIN32

   SOCKET sock = 0;
   int protocol;

   union {
      SOCKADDR_IN   ipv4;
      SOCKADDR_IN6 ipv6;
   } addr;

#elif defined(__unix__)

   int sock = 0;
   int protocol;

   union {
      struct sockaddr_in  ipv4;
      struct sockaddr_in6 ipv6;
   } addr;

#endif

public:

   enum Option {
      /* no special options */
      NONE        = 0,
      /* use tcp protocol for connection */
      TCP         = 0,
      /* use udp protocol for connection */
      UDP         = 1,
      /* set the socket as nonblocking */
      NONBLOCKING = 2,
      /* set in verbose mode, print all steps */
      VERBOSE     = 4,
      DEBUG       = 4,
      /* attempt only IPV4 addresses */
      IPV4        = 8,
      /* attempt only IPV6 addresses */
      IPV6        = 16,
   };

   WiredLink(uint options = NONE | TCP, std::string verbose_prompt = "WiredLink");
   ~WiredLink();

   /* attempt to open a connection to addr:port, where
    * addr can either be a valid ipv4 or ipv6 address,
    * or a hostname that can be resolved via getaddrinfo. A
    * zero is returned on success, and -1 is returned on 
    * failure. errno is set by one of the internal functions
    * called on an error, leaving the class in an
    * undetermined state. Call close and attempt to reopen if
    * this occurs and you are sure the connection can be made.*/
   int open(std::string addr, uint port);

   /* close any open connection, resetting the class.
    * Return the result of the internal attempt to
    * close the socket, so -1 on failure and 0 on
    * success. This result can be safely ignored though,
    * as POSIX discourages the recalling of close. */
   int close();

   /* send len bytes of data over the link. Return
    * the number of bytes sent, or -1 on error    */
   long send(const uint8_t * data, size_t len);

   /* recieve len bytes of data over the link. Return
    * the number of bytes recieved, or -1 on error  */
   long recv(uint8_t * data, size_t len);

   /* returns true if the current connection is still
    * open to the best knowledge of the link. A false
    * value fron this call should be followed by a
    * call to close from the user, as the connection
    * is no longer open.                            */
   bool live();

};

}

#endif
