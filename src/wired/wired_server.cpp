
#include "wired_server.h"
#include "wired_windows_support.h"

namespace Rhizar16 {

#ifdef _WIN32
int __RHIZAR16_WSASTARTUP_CALLED__ = 0;

WiredServer::WiredServer(uint verbose, std::string verbose_prompt)
   : verbose(verbose) {
   this->verbose_prompt = verbose_prompt;
   this->connection_pos = 0;
   this->connection_len = __RHIZAR16_WIRED_SERV_INITIAL_CONNECTIONS__;
   this->connections = (struct pollfd *)malloc(sizeof(struct pollfd)*this->connection_len);
   ZeroMemory(connections,sizeof(WSAPOLLFD)*this->connection_len);
   for (uint i = 0; i < connection_len; ++i)
      connections[i].fd = INVALID_SOCKET;

   if (__RHIZAR16_WSASTARTUP_CALLED__ == 0) {
      WSADATA wsa_data;
      WSAStartup(MAKEWORD(2,2),&wsa_data);
      __RHIZAR16_WSASTARTUP_CALLED__ = 1;
   }
}

WiredServer::~WiredServer() {
   finish();
   free(connections);
}

void WiredServer::add_connection(socktype sock) {

   for (uint i = 0; i < connection_pos; ++i) {
      if (connections[i].fd == INVALID_SOCKET) {
         connections[i].fd = sock;
         connections[i].events = POLLRDNORM | POLLWRNORM;
         return;
      }
   }

   if (connection_pos == connection_len) {
      WSAPOLLFD * new_connections;
      new_connections = (WSAPOLLFD *)realloc(connections,connection_len*2*sizeof(WSAPOLLFD));
      if (new_connections == NULL) {
         /* abandon the new file descriptor */

         if (verbose)
            printf("%s: out of memory, failed to add new socket connection\n",verbose_prompt.c_str());

         shutdown(sock,SD_BOTH);
         closesocket(sock);
         return;
      }
      else {
         connections = new_connections;
         ZeroMemory(connections+connection_len,sizeof(WSAPOLLFD)*connection_len);
         for (uint i = connection_len; i < connection_len+connection_len; ++i)
            connections[i].fd = INVALID_SOCKET;
         connection_len *= 2;
      }
   }

   connections[connection_pos].fd = sock;
   connections[connection_pos].events = POLLRDNORM | POLLWRNORM;

   connection_pos += 1;
}

void WiredServer::rem_connection(socktype sock) {

   for (uint i = 0; i < connection_pos; ++i) {

      if (connections[i].fd == sock || ~(connections[i].fd) == sock) {
         ZeroMemory(&connections[i],sizeof(WSAPOLLFD));
         connections[i].fd = INVALID_SOCKET;
      }
   }
}

int WiredServer::start(uint port) {
   static const int yes = 1;

   finish();

   mux.lock();

   if (verbose)
      printf("%s: initializing server on port %d\n",verbose_prompt.c_str(),port);

   listen_ipv4 = socket(AF_INET,SOCK_STREAM,0);

   if (listen_ipv4 == INVALID_SOCKET) {

      if (verbose)
         printf("%s: failed to initialize listening socket for the IPv4 protocol with error %s\n",
                verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());
      
      goto failure;
   }

   if (setsockopt(listen_ipv4,SOL_SOCKET,SO_REUSEADDR,(char *)&yes,sizeof(int)) == SOCKET_ERROR) {

      if (verbose)
         printf("%s failed to set SO_REUSEADDR option on IPv4 listen socket with error %s\n",
                verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

      goto failure;
   }

   struct sockaddr_in sockaddr_ipv4;
   ZeroMemory(&sockaddr_ipv4,sizeof(SOCKADDR_IN));
   sockaddr_ipv4.sin_family = AF_INET;
   sockaddr_ipv4.sin_port = htons(port);
   sockaddr_ipv4.sin_addr.s_addr = INADDR_ANY;

   if (bind(listen_ipv4,(SOCKADDR *)&sockaddr_ipv4,sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {

      if (verbose)
         printf("%s: failed to bind IPv4 listen socket with error %s\n",
                verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

      goto failure;
   }

   /* try to hold the maximum number of connections possible */
   if (listen(listen_ipv4,SOMAXCONN) == SOCKET_ERROR) {

      if (verbose)
         printf("%s: failed to set IPv4 listen socket queue with error %s\n",
                verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

      goto failure;
   }

   listen_ipv6 = socket(AF_INET6,SOCK_STREAM,0);

   if (listen_ipv6 == INVALID_SOCKET) {

      if (verbose)
         printf("%s: failed to initialize listening socket for the IPv6 protocol with error %s\n",
                verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

      goto failure;
   }

   if (setsockopt(listen_ipv6,SOL_SOCKET,SO_REUSEADDR,(char *)&yes,sizeof(int)) == SOCKET_ERROR) {

      if (verbose)
         printf("%s failed to set SO_REUSEADDR option on IPv4 listen socket with error %s\n",
                verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

      goto failure;
   }

   if (setsockopt(listen_ipv6,IPPROTO_IPV6,IPV6_V6ONLY,(char *)&yes,sizeof(int)) == SOCKET_ERROR) {

      if (verbose)
         printf("%s failed to set IPV6_ONLY option on IPv4 listen socket with error %s\n",
                verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

      goto failure;
   }

   SOCKADDR_IN6 sockaddr_ipv6;
   ZeroMemory(&sockaddr_ipv6,sizeof(SOCKADDR_IN6));
   sockaddr_ipv6.sin6_family = AF_INET6;
   sockaddr_ipv6.sin6_port = htons(port);
   memcpy(&sockaddr_ipv6.sin6_addr,&in6addr_any,sizeof(IN6_ADDR));
   sockaddr_ipv6.sin6_flowinfo = 0;
   sockaddr_ipv6.sin6_scope_id = 0;

   if (bind(listen_ipv6,(SOCKADDR *)&sockaddr_ipv6,sizeof(SOCKADDR_IN6)) == SOCKET_ERROR) {

      if (verbose)
         printf("%s: failed to bind IPv6 listen socket with error %s\n",
                verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

      goto failure;
   }

   /* try to hold the maximum number of connections possible */
   if (listen(listen_ipv6,SOMAXCONN) == SOCKET_ERROR) {

      if (verbose)
         printf("%s: failed to set IPv4 listen socket queue with error %s\n",
                verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

      goto failure;
   }

   if (verbose)
      printf("%s: listeners started\n",verbose_prompt.c_str());

   add_connection(listen_ipv4);
   add_connection(listen_ipv6);

   if (verbose)
      printf("%s: manager started\n",verbose_prompt.c_str());

   manager = std::thread(&WiredServer::manage,this);

   mux.unlock();

   return 0;

failure:
   if (listen_ipv4 != INVALID_SOCKET)
      closesocket(listen_ipv4);
   if (listen_ipv6 != INVALID_SOCKET)
      closesocket(listen_ipv6);
   mux.unlock();
   return -1;
}

void WiredServer::finish() {

   mux.lock();

   for (u_int i = 0; i < connection_pos; ++i) {
      if (connections[i].fd == INVALID_SOCKET)
         continue;
      closesocket(connections[i].fd);
   }
   ZeroMemory(connections,sizeof(WSAPOLLFD)*connection_len);

   connection_pos = 0;

   actions.clear();

   mux.unlock();

   if (manager.joinable())
      manager.join();
}

void WiredServer::manage() {
   int ready_count;

   for ( ; ; ) {
      mux.lock();

      if (connection_pos == 0) {
         mux.unlock();
         return;
      }

      ready_count = WSAPoll(connections,connection_pos,1);

      if (ready_count > 0) {

         for (uint i = 0; i < connection_pos; ++i) {

            if (actions[connections[i].fd].state == CLOSED)
               continue;

            if (connections[i].revents & POLLRDNORM) {

               /* handle incoming ipv4 connections */
               if (connections[i].fd == listen_ipv4) {

                  SOCKADDR_IN new_ipv4_addr;
                  ZeroMemory(&new_ipv4_addr,sizeof(SOCKADDR_IN));
                  socklen_t new_ipv4_addr_len = sizeof(SOCKADDR_IN);
                  SOCKET new_ipv4 = accept(listen_ipv4,(SOCKADDR *)&new_ipv4_addr,&new_ipv4_addr_len);

                  if (new_ipv4 == INVALID_SOCKET) {

                     if (verbose) {

                        char buf[INET_ADDRSTRLEN];
                        inet_ntop(AF_INET,&new_ipv4_addr.sin_addr,buf,INET_ADDRSTRLEN);

                        printf("%s: failed to accept IPv4 connection from address %s with error %s\n",
                               verbose_prompt.c_str(),buf, WinOnly::print_sockerr().c_str());
                     }

                     continue;
                  }

                  {
                     u_long yes = 1;
                     if (ioctlsocket(new_ipv4,FIONBIO,&yes) == SOCKET_ERROR) {

                        if (verbose)
                           printf("%s: attempt to configure socket as nonblocking failed with error %s\n",
                                  verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

                        continue;
                     }
                  }

                  add_connection(new_ipv4);
                  actions[new_ipv4].state = READY;
                  memcpy(&actions[new_ipv4].addr.ipv4,&new_ipv4_addr,new_ipv4_addr_len);

                  if (verbose) {

                     char buf[INET_ADDRSTRLEN];
                     inet_ntop(AF_INET,&new_ipv4_addr.sin_addr,buf,INET_ADDRSTRLEN);

                     printf("%s: accepted IPv4 connection from address %s as %llu\n",
                            verbose_prompt.c_str(),buf,new_ipv4);
                  }

                  continue;
               }

               /* handle incoming ipv6 connections */
               if (connections[i].fd == listen_ipv6) {

                  SOCKADDR_IN6 new_ipv6_addr;
                  ZeroMemory(&new_ipv6_addr,sizeof(SOCKADDR_IN6));
                  socklen_t new_ipv6_addr_len = sizeof(SOCKADDR_IN6);
                  SOCKET new_ipv6 = accept(listen_ipv6,(SOCKADDR *)&new_ipv6_addr,&new_ipv6_addr_len);

                  if (new_ipv6 == INVALID_SOCKET) {

                     if (verbose) {

                        char buf[INET6_ADDRSTRLEN];
                        inet_ntop(AF_INET6,&new_ipv6_addr.sin6_addr,buf,INET6_ADDRSTRLEN);

                        printf("%s: failed to accept IPv6 connection from address %s with error %s\n",
                               verbose_prompt.c_str(),buf, WinOnly::print_sockerr().c_str());
                     }

                     continue;
                  }

                  {
                     u_long yes = 1;
                     if (ioctlsocket(new_ipv6,FIONBIO,&yes) == SOCKET_ERROR) {

                        if (verbose)
                           printf("%s: attempt to configure socket as nonblocking failed with error %s\n",
                                  verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

                        continue;
                     }
                  }

                  add_connection(new_ipv6);
                  actions[new_ipv6].state = READY;
                  memcpy(&actions[new_ipv6].addr.ipv6,&new_ipv6_addr,new_ipv6_addr_len);

                  if (verbose) {

                     char buf[INET6_ADDRSTRLEN];
                     inet_ntop(AF_INET6,&new_ipv6_addr.sin6_addr,buf,INET6_ADDRSTRLEN);

                     printf("%s: accepted IPv6 connection from address %s as %llu\n",
                            verbose_prompt.c_str(),buf,new_ipv6);
                  }

                  continue;
               }

               if (actions[connections[i].fd].state == READING) {

                  int res = 0;

                  do {

                     res = ::recv(connections[i].fd,
                                  (char *)
                                  actions[connections[i].fd].data +
                                  actions[connections[i].fd].completed,
                                  actions[connections[i].fd].remaining,
                                  0);

                     int lerr = WSAGetLastError();

                     if (res == 0)
                        goto closed;

                     if (res == SOCKET_ERROR) {

                        if (lerr == WSAEINTR)
                           continue;

                        if (lerr == WSAEWOULDBLOCK)
                           break;
                        if (errno == EINTR)
                           continue;
closed:

                        if (verbose) {

                           char buf[INET6_ADDRSTRLEN];
                           if (actions[connections[i].fd].addr.ipv4.sin_family == AF_INET)
                              inet_ntop(AF_INET,&actions[connections[i].fd].addr.ipv4.sin_addr,buf,INET6_ADDRSTRLEN);
                           else
                              inet_ntop(AF_INET6,&actions[connections[i].fd].addr.ipv6.sin6_addr,buf,INET6_ADDRSTRLEN);

                           printf("%s: connection to %s as %llu closed\n",
                                  verbose_prompt.c_str(),buf,connections[i].fd);
                        }

                        shutdown(connections[i].fd,SD_BOTH);
                        closesocket(connections[i].fd);
                        actions[connections[i].fd].state = CLOSED;
                        break;
                     }

                     actions[connections[i].fd].remaining -= res;
                     actions[connections[i].fd].completed += res;

                     if (actions[connections[i].fd].remaining == 0) {
                        actions[connections[i].fd].state = READY;
                        break;
                     }

                  } while ( 1 );
               }
               else {

                  /* check if the read is due to the socket being closed */
                  int tiny_buf;
                  if (::recv(connections[i].fd,(char *)&tiny_buf,1,MSG_PEEK) == 0) {
                     shutdown(connections[i].fd,SD_BOTH);
                     closesocket(connections[i].fd);
                     actions[connections[i].fd].state = CLOSED;

                     if (verbose) {

                        char buf[INET6_ADDRSTRLEN];
                        if (actions[connections[i].fd].addr.ipv4.sin_family == AF_INET)
                           inet_ntop(AF_INET,&actions[connections[i].fd].addr.ipv4.sin_addr,buf,INET6_ADDRSTRLEN);
                        else
                           inet_ntop(AF_INET6,&actions[connections[i].fd].addr.ipv6.sin6_addr,buf,INET6_ADDRSTRLEN);

                        printf("%s: connection to %s as %llu closed\n",
                               verbose_prompt.c_str(),buf,connections[i].fd);
                     }

                     break;
                  }
               }
            }

            if (connections[i].revents & POLLWRNORM) {

               if (actions[connections[i].fd].state == WRITING) {

                  int res = 0;

                  do {

                     res = ::send(connections[i].fd,
                                  (char *)
                                  actions[connections[i].fd].data +
                                  actions[connections[i].fd].completed,
                                  actions[connections[i].fd].remaining,
                                  0);

                     if (res == -1) {
                        int lerr = WSAGetLastError();

                        if (lerr == WSAEINTR)
                           continue;

                        if (lerr == WSAEWOULDBLOCK)
                           break;

                        if (verbose) {

                           char buf[INET6_ADDRSTRLEN];
                           if (actions[connections[i].fd].addr.ipv4.sin_family == AF_INET)
                              inet_ntop(AF_INET,&actions[connections[i].fd].addr.ipv4.sin_addr,buf,INET6_ADDRSTRLEN);
                           else
                              inet_ntop(AF_INET6,&actions[connections[i].fd].addr.ipv6.sin6_addr,buf,INET6_ADDRSTRLEN);

                           printf("%s: connection to %s as %llu closed\n",
                                  verbose_prompt.c_str(),buf,connections[i].fd);
                        }

                        shutdown(connections[i].fd,SD_BOTH);
                        closesocket(connections[i].fd);
                        actions[connections[i].fd].state = CLOSED;
                        break;
                     }

                     actions[connections[i].fd].remaining -= res;
                     actions[connections[i].fd].completed += res;

                     if (actions[connections[i].fd].remaining == 0) {
                        actions[connections[i].fd].state = READY;
                        break;
                     }

                  } while ( 1 );
               }
            }
         }
      }

      mux.unlock();
      std::this_thread::yield();
   }
}

int WiredServer::get_ready(std::vector<socktype> & collection) {
   int ready_count = 0;

   mux.lock();

   for (uint i = 0; i < connection_pos; ++i) {
      if (actions[connections[i].fd].state == READY) {
         collection.push_back(connections[i].fd);
         ready_count += 1;
      }
   }

   mux.unlock();

   return ready_count;
}

int WiredServer::wait_ready(std::vector<socktype> & collection, std::chrono::nanoseconds timeout) {
   int ready_count = 0;

   if (timeout == std::chrono::nanoseconds(0)) {
      do {
         ready_count = get_ready(collection);
         std::this_thread::yield();
      } while (!ready_count);
   }
   else {
      auto start = std::chrono::steady_clock::now();
      do {
         ready_count = get_ready(collection);
         std::this_thread::yield();
      } while (!ready_count && 
               std::chrono::nanoseconds(std::chrono::steady_clock::now() - start) < timeout);
   }

   return ready_count;
}

int WiredServer::send(socktype socket, uint8_t * data, size_t len) {
   int retval = 0;

   mux.lock();

   if (actions[socket].state == READY) {
      actions[socket].data = data;
      actions[socket].remaining = len;
      actions[socket].completed = 0;
      actions[socket].state = WRITING;
   }
   else
      retval = -1;

   mux.unlock();

   return retval;
}

int WiredServer::recv(socktype socket, uint8_t * data, size_t len) {
   int retval = 0;

   mux.lock();

   if (actions[socket].state == READY) {
      actions[socket].data = data;
      actions[socket].remaining = len;
      actions[socket].completed = 0;
      actions[socket].state = READING;
   }
   else
      retval = -1;

   mux.unlock();

   return retval;
}

int WiredServer::get_closed(std::vector<socktype> & collection) {
   int closed_count = 0;

   mux.lock();

   for (uint i = 0; i < connection_pos; ++i) {
      if (actions[connections[i].fd].state == CLOSED) {
         collection.push_back(connections[i].fd);
         closed_count += 1;
      }
   }

   mux.unlock();

   return closed_count;
}

int WiredServer::close(socktype socket) {

   if (actions[socket].state == UNKNOWN)
      return 0;

   mux.lock();

   actions[socket].state = CLOSED;
   shutdown(socket,SD_BOTH);
   int res = closesocket(socket);

   if (verbose) {

      char buf[INET6_ADDRSTRLEN];
      if (actions[socket].addr.ipv4.sin_family == AF_INET)
         inet_ntop(AF_INET,&actions[socket].addr.ipv4.sin_addr,buf,INET6_ADDRSTRLEN);
      else
         inet_ntop(AF_INET6,&actions[socket].addr.ipv6.sin6_addr,buf,INET6_ADDRSTRLEN);

      printf("%s: connection to %s as %llu closed\n",
             verbose_prompt.c_str(),buf,socket);
   }

   mux.unlock();

   return res;
}

int WiredServer::clean() {
   int clean_count = 0;

   mux.lock();

   for (uint i = 0; i < connection_pos; ++i) {
      if (actions[connections[i].fd].state == CLOSED) {
         rem_connection(connections[i].fd);
         clean_count += 1;
      }
   }

   mux.unlock();

   return clean_count;
}

#elif defined(__unix__)

WiredServer::WiredServer(uint verbose, std::string verbose_prompt)
   : verbose(verbose) {
   this->verbose_prompt = verbose_prompt;
   this->connection_pos = 0;
   this->connection_len = __RHIZAR16_WIRED_SERV_INITIAL_CONNECTIONS__;
   this->connections = (struct pollfd *)malloc(sizeof(struct pollfd)*this->connection_len);
   bzero(connections,sizeof(struct pollfd)*this->connection_len);
}

WiredServer::~WiredServer() {
   finish();
   free(connections);
}

void WiredServer::add_connection(socktype sock) {

   for (uint i = 0; i < connection_pos; ++i) {
      if (connections[i].fd == 0) {
         connections[i].fd = sock;
         connections[i].events = POLLIN | POLLOUT;
         return;
      }
   }

   if (connection_pos == connection_len) {
      struct pollfd * new_connections;
      new_connections = (struct pollfd *)realloc(connections,connection_len*2*sizeof(struct pollfd));
      if (new_connections == NULL) {
         /* abandon the new file descriptor */

         if (verbose)
            printf("%s: out of memory, failed to add new socket connection\n",verbose_prompt.c_str());

         ::close(sock);
         return;
      }
      else {
         connections = new_connections;
         bzero(connections+connection_len,sizeof(struct pollfd)*connection_len);
         connection_len *= 2;
      }
   }

   connections[connection_pos].fd = sock;
   connections[connection_pos].events = POLLIN | POLLOUT;

   connection_pos += 1;
}

void WiredServer::rem_connection(socktype sock) {

   for (uint i = 0; i < connection_pos; ++i) {

      if (connections[i].fd == sock || ~(connections[i].fd) == sock) {
         bzero(&connections[i],sizeof(struct pollfd));
      }
   }
}

int WiredServer::start(uint port) {
   static const int yes = 1;

   finish();

   mux.lock();

   if (verbose)
      printf("%s: initializing server on port %d\n",verbose_prompt.c_str(),port);

   listen_ipv4 = socket(AF_INET,SOCK_STREAM,0);

   if (listen_ipv4 == -1) {

      if (verbose)
         printf("%s: failed to initialize listening socket for the IPv4 protocol\n",
                verbose_prompt.c_str());
      
      goto failure;
   }

   if (setsockopt(listen_ipv4,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {

      if (verbose)
         printf("%s failed to set SO_REUSEADDR option on IPv4 listen socket\n",
                verbose_prompt.c_str());

      goto failure;
   }

   struct sockaddr_in sockaddr_ipv4;
   bzero(&sockaddr_ipv4,sizeof(struct sockaddr_in));
   sockaddr_ipv4.sin_family = AF_INET;
   sockaddr_ipv4.sin_port = htons(port);
   sockaddr_ipv4.sin_addr.s_addr = INADDR_ANY;

   if (bind(listen_ipv4,(struct sockaddr *)&sockaddr_ipv4,sizeof(struct sockaddr_in)) == -1) {

      if (verbose)
         printf("%s: failed to bind IPv4 listen socket\n",verbose_prompt.c_str());

      goto failure;
   }

   /* try to hold the maximum number of connections possible */
   if (listen(listen_ipv4,INT_MAX) == -1) {

      if (verbose)
         printf("%s: failed to set IPv4 listen socket queue\n",verbose_prompt.c_str());

      goto failure;
   }

   listen_ipv6 = socket(AF_INET6,SOCK_STREAM,0);

   if (listen_ipv6 == -1) {

      if (verbose)
         printf("%s: failed to initialize listening socket for the IPv6 protocol\n",
                verbose_prompt.c_str());

      goto failure;
   }

   if (setsockopt(listen_ipv6,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {

      if (verbose)
         printf("%s failed to set SO_REUSEADDR option on IPv4 listen socket\n",
                verbose_prompt.c_str());

      goto failure;
   }

   if (setsockopt(listen_ipv6,IPPROTO_IPV6,IPV6_V6ONLY,&yes,sizeof(int)) == -1) {

      if (verbose)
         printf("%s failed to set IPV6_ONLY option on IPv4 listen socket\n",
                verbose_prompt.c_str());

      goto failure;
   }

   struct sockaddr_in6 sockaddr_ipv6;
   bzero(&sockaddr_ipv6,sizeof(struct sockaddr_in6));
   sockaddr_ipv6.sin6_family = AF_INET6;
   sockaddr_ipv6.sin6_port = htons(port);
   memcpy(&sockaddr_ipv6.sin6_addr,&in6addr_any,sizeof(struct in6_addr));
   sockaddr_ipv6.sin6_flowinfo = 0;
   sockaddr_ipv6.sin6_scope_id = 0;

   if (bind(listen_ipv6,(struct sockaddr *)&sockaddr_ipv6,sizeof(struct sockaddr_in6)) == -1) {

      if (verbose)
         printf("%s: failed to bind IPv6 listen socket\n",verbose_prompt.c_str());

      goto failure;
   }

   /* try to hold the maximum number of connections possible */
   if (listen(listen_ipv6,INT_MAX) == -1) {

      if (verbose)
         printf("%s: failed to set IPv4 listen socket queue\n",verbose_prompt.c_str());

      goto failure;
   }

   if (verbose)
      printf("%s: listeners started\n",verbose_prompt.c_str());

   add_connection(listen_ipv4);
   add_connection(listen_ipv6);

   if (verbose)
      printf("%s: manager started\n",verbose_prompt.c_str());

   manager = std::thread(&WiredServer::manage,this);

   mux.unlock();

   return 0;

failure:
   if (listen_ipv4)
      ::close(listen_ipv4);
   if (listen_ipv6)
      ::close(listen_ipv6);
   mux.unlock();
   return -1;
}

void WiredServer::finish() {

   mux.lock();

   for (uint i = 0; i < connection_pos; ++i) {
      if (connections[i].fd > 0)
         ::close(connections[i].fd);
      else if (connections[i].fd < 0)
         ::close(~(connections[i].fd));
   }
   bzero(connections,sizeof(struct pollfd)*connection_len);

   connection_pos = 0;

   actions.clear();

   mux.unlock();

   if (manager.joinable())
      manager.join();
}

void WiredServer::manage() {
   int ready_count;

   for ( ; ; ) {
      mux.lock();

      if (connection_pos == 0) {
         mux.unlock();
         return;
      }

      ready_count = poll(connections,connection_pos,1);

      if (ready_count) {

         for (uint i = 0; i < connection_pos; ++i) {

            if (actions[connections[i].fd].state == CLOSED)
               continue;

            if (connections[i].revents & POLLIN) {

               /* handle incoming ipv4 connections */
               if (connections[i].fd == listen_ipv4) {

                  struct sockaddr_in new_ipv4_addr;
                  bzero(&new_ipv4_addr,sizeof(struct sockaddr_in));
                  socklen_t new_ipv4_addr_len = sizeof(struct sockaddr_in);
                  int new_ipv4 = accept(listen_ipv4,(struct sockaddr *)&new_ipv4_addr,&new_ipv4_addr_len);

                  if (new_ipv4 == -1) {

                     if (verbose) {

                        char buf[INET_ADDRSTRLEN];
                        inet_ntop(AF_INET,&new_ipv4_addr.sin_addr,buf,INET_ADDRSTRLEN);

                        printf("%s: failed to accept IPv4 connection from address %s\n",
                               verbose_prompt.c_str(),buf);
                     }

                     continue;
                  }

                  add_connection(new_ipv4);
                  actions[new_ipv4].state = READY;
                  memcpy(&actions[new_ipv4].addr.ipv4,&new_ipv4_addr,new_ipv4_addr_len);

                  if (verbose) {

                     char buf[INET_ADDRSTRLEN];
                     inet_ntop(AF_INET,&new_ipv4_addr.sin_addr,buf,INET_ADDRSTRLEN);

                     printf("%s: accepted IPv4 connection from address %s as %d\n",
                            verbose_prompt.c_str(),buf,new_ipv4);
                  }

                  continue;
               }

               /* handle incoming ipv6 connections */
               if (connections[i].fd == listen_ipv6) {

                  struct sockaddr_in6 new_ipv6_addr;
                  bzero(&new_ipv6_addr,sizeof(struct sockaddr_in6));
                  socklen_t new_ipv6_addr_len = sizeof(struct sockaddr_in6);
                  int new_ipv6 = accept(listen_ipv6,(struct sockaddr *)&new_ipv6_addr,&new_ipv6_addr_len);

                  if (new_ipv6 == -1) {

                     if (verbose) {

                        char buf[INET6_ADDRSTRLEN];
                        inet_ntop(AF_INET6,&new_ipv6_addr.sin6_addr,buf,INET6_ADDRSTRLEN);

                        printf("%s: failed to accept IPv6 connection from address %s\n",
                               verbose_prompt.c_str(),buf);
                     }

                     continue;
                  }

                  add_connection(new_ipv6);
                  actions[new_ipv6].state = READY;
                  memcpy(&actions[new_ipv6].addr.ipv6,&new_ipv6_addr,new_ipv6_addr_len);

                  if (verbose) {

                     char buf[INET6_ADDRSTRLEN];
                     inet_ntop(AF_INET6,&new_ipv6_addr.sin6_addr,buf,INET6_ADDRSTRLEN);

                     printf("%s: accepted IPv6 connection from address %s as %d\n",
                            verbose_prompt.c_str(),buf,new_ipv6);
                  }

                  continue;
               }

               if (actions[connections[i].fd].state == READING) {

                  int res = 0;

                  do {

                     res = ::recv(connections[i].fd,
                                  actions[connections[i].fd].data +
                                  actions[connections[i].fd].completed,
                                  actions[connections[i].fd].remaining,
                                  MSG_DONTWAIT);

                     if (res == 0)
                        goto closed;

                     if (res == -1) {
                        if (errno == EINTR)
                           continue;
#if EAGAIN == EWOULDBLOCK
                        if (errno == EAGAIN)
#else
                        if (errno == EAGAIN || errno == EWOULDBLOCK)
#endif
                           break;
closed:

                        if (verbose) {

                           char buf[INET6_ADDRSTRLEN];
                           if (actions[connections[i].fd].addr.ipv4.sin_family == AF_INET)
                              inet_ntop(AF_INET,&actions[connections[i].fd].addr.ipv4.sin_addr,buf,INET6_ADDRSTRLEN);
                           else
                              inet_ntop(AF_INET6,&actions[connections[i].fd].addr.ipv6.sin6_addr,buf,INET6_ADDRSTRLEN);

                           printf("%s: connection to %s as %d closed\n",
                                  verbose_prompt.c_str(),buf,connections[i].fd);
                        }

                        ::close(connections[i].fd);
                        actions[connections[i].fd].state = CLOSED;
                        break;
                     }

                     actions[connections[i].fd].remaining -= res;
                     actions[connections[i].fd].completed += res;

                     if (actions[connections[i].fd].remaining == 0) {
                        actions[connections[i].fd].state = READY;
                        break;
                     }

                  } while ( 1 );
               }
               else {

                  /* check if the read is due to the socket being closed */
                  int tiny_buf;
                  if (::recv(connections[i].fd,&tiny_buf,1,MSG_PEEK) == 0) {
                     ::close(connections[i].fd);
                     actions[connections[i].fd].state = CLOSED;

                     if (verbose) {

                        char buf[INET6_ADDRSTRLEN];
                        if (actions[connections[i].fd].addr.ipv4.sin_family == AF_INET)
                           inet_ntop(AF_INET,&actions[connections[i].fd].addr.ipv4.sin_addr,buf,INET6_ADDRSTRLEN);
                        else
                           inet_ntop(AF_INET6,&actions[connections[i].fd].addr.ipv6.sin6_addr,buf,INET6_ADDRSTRLEN);

                        printf("%s: connection to %s as %d closed\n",
                               verbose_prompt.c_str(),buf,connections[i].fd);
                     }

                     break;
                  }
               }
            }

            if (connections[i].revents & POLLOUT) {

               if (actions[connections[i].fd].state == WRITING) {

                  int res = 0;

                  do {

                     res = ::send(connections[i].fd,
                                  actions[connections[i].fd].data +
                                  actions[connections[i].fd].completed,
                                  actions[connections[i].fd].remaining,
                                  MSG_DONTWAIT | MSG_NOSIGNAL);

                     if (res == -1) {
                        if (errno == EINTR)
                           continue;
#if EAGAIN == EWOULDBLOCK
                        if (errno == EAGAIN)
#else
                        if (errno == EAGAIN || errno == EWOULDBLOCK)
#endif
                           break;

                        if (verbose) {

                           char buf[INET6_ADDRSTRLEN];
                           if (actions[connections[i].fd].addr.ipv4.sin_family == AF_INET)
                              inet_ntop(AF_INET,&actions[connections[i].fd].addr.ipv4.sin_addr,buf,INET6_ADDRSTRLEN);
                           else
                              inet_ntop(AF_INET6,&actions[connections[i].fd].addr.ipv6.sin6_addr,buf,INET6_ADDRSTRLEN);

                           printf("%s: connection to %s as %d closed\n",
                                  verbose_prompt.c_str(),buf,connections[i].fd);
                        }

                        ::close(connections[i].fd);
                        actions[connections[i].fd].state = CLOSED;
                        break;
                     }

                     actions[connections[i].fd].remaining -= res;
                     actions[connections[i].fd].completed += res;

                     if (actions[connections[i].fd].remaining == 0) {
                        actions[connections[i].fd].state = READY;
                        break;
                     }

                  } while ( 1 );
               }
            }
         }
      }

      mux.unlock();
      std::this_thread::yield();
   }
}

int WiredServer::get_ready(std::vector<socktype> & collection) {
   int ready_count = 0;

   mux.lock();

   for (uint i = 0; i < connection_pos; ++i) {
      if (actions[connections[i].fd].state == READY) {
         collection.push_back(connections[i].fd);
         ready_count += 1;
      }
   }

   mux.unlock();

   return ready_count;
}

int WiredServer::wait_ready(std::vector<socktype> & collection, std::chrono::nanoseconds timeout) {
   int ready_count = 0;

   if (timeout == std::chrono::nanoseconds(0)) {
      do {
         ready_count = get_ready(collection);
         std::this_thread::yield();
      } while (!ready_count);
   }
   else {
      auto start = std::chrono::steady_clock::now();
      do {
         ready_count = get_ready(collection);
         std::this_thread::yield();
      } while (!ready_count && 
               std::chrono::nanoseconds(std::chrono::steady_clock::now() - start) < timeout);
   }

   return ready_count;
}

int WiredServer::send(socktype socket, uint8_t * data, size_t len) {
   int retval = 0;

   mux.lock();

   if (actions[socket].state == READY) {
      actions[socket].data = data;
      actions[socket].remaining = len;
      actions[socket].completed = 0;
      actions[socket].state = WRITING;
   }
   else
      retval = -1;

   mux.unlock();

   return retval;
}

int WiredServer::recv(socktype socket, uint8_t * data, size_t len) {
   int retval = 0;

   mux.lock();

   if (actions[socket].state == READY) {
      actions[socket].data = data;
      actions[socket].remaining = len;
      actions[socket].completed = 0;
      actions[socket].state = READING;
   }
   else
      retval = -1;

   mux.unlock();

   return retval;
}

int WiredServer::get_closed(std::vector<socktype> & collection) {
   int closed_count = 0;

   mux.lock();

   for (uint i = 0; i < connection_pos; ++i) {
      if (actions[connections[i].fd].state == CLOSED) {
         collection.push_back(connections[i].fd);
         closed_count += 1;
      }
   }

   mux.unlock();

   return closed_count;
}

int WiredServer::close(socktype socket) {

   if (actions[socket].state == UNKNOWN)
      return 0;

   mux.lock();

   actions[socket].state = CLOSED;
   int res = ::close(socket);

   if (verbose) {

      char buf[INET6_ADDRSTRLEN];
      if (actions[socket].addr.ipv4.sin_family == AF_INET)
         inet_ntop(AF_INET,&actions[socket].addr.ipv4.sin_addr,buf,INET6_ADDRSTRLEN);
      else
         inet_ntop(AF_INET6,&actions[socket].addr.ipv6.sin6_addr,buf,INET6_ADDRSTRLEN);

      printf("%s: connection to %s as %d closed\n",
             verbose_prompt.c_str(),buf,socket);
   }

   mux.unlock();

   return res;
}

int WiredServer::clean() {
   int clean_count = 0;

   mux.lock();

   for (uint i = 0; i < connection_pos; ++i) {
      if (actions[connections[i].fd].state == CLOSED) {
         rem_connection(connections[i].fd);
         clean_count += 1;
      }
   }

   mux.unlock();

   return clean_count;
}

#endif

}

