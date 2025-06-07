
#include "wired_link.h"
#include "wired_windows_support.h"

namespace Rhizar16 {

#ifdef _WIN32

WiredLink::WiredLink(uint options, std::string verbose_prompt) 
   : options(options) {
   this->verbose_prompt = verbose_prompt;
   this->is_live = false;

   if (__RHIZAR16_WSASTARTUP_CALLED__ == 0) {
      WSADATA wsa_data;
      WSAStartup(MAKEWORD(2,2),&wsa_data);
      __RHIZAR16_WSASTARTUP_CALLED__ = 1;
   }
}

WiredLink::~WiredLink() {
   if (sock) {
      shutdown(sock,SD_BOTH);
      closesocket(sock);
   }
}

int WiredLink::open(std::string addr, uint port) {

   if (options & VERBOSE) {
      if (options & UDP)
         printf("%s: opening socket using UDP protocol\n",verbose_prompt.c_str());
      else
         printf("%s: opening socket using TCP protocol\n",verbose_prompt.c_str());

      if (options & NONBLOCKING)
         printf("%s: configuring socket in nonblocking mode\n",verbose_prompt.c_str());

      printf("%s: connecting to address %s at port %u\n",
             verbose_prompt.c_str(),addr.c_str(),port);
   }


   int retval = -1;

   ADDRINFO hints;
   ZeroMemory(&hints,sizeof(struct addrinfo));
   if (((options & IPV4) && (options & IPV6)) || !(options & (IPV4 | IPV6))) {

      if (options & VERBOSE)
         printf("%s: Attempting to collect suitable addresses for %s via protocol IPv4, IPv6\n",
                verbose_prompt.c_str(),addr.c_str());

      hints.ai_family = AF_UNSPEC;
   }
   else if (options & IPV4) {

      if (options & VERBOSE)
         printf("%s: Attempting to collect suitable addresses for %s via protocol IPv4\n",
                verbose_prompt.c_str(),addr.c_str());

      hints.ai_family = AF_INET;
   }
   else if (options & IPV6) {

      if (options & VERBOSE)
         printf("%s: Attempting to collect suitable addresses for %s via protocol IPv6\n",
                verbose_prompt.c_str(),addr.c_str());

      hints.ai_family = AF_INET6;
   }
   hints.ai_flags = AI_ADDRCONFIG;

   ADDRINFO * res;
   int getaddrinfo_res;
   if ( (getaddrinfo_res = getaddrinfo(addr.c_str(),NULL,&hints,&res)) != 0) {

      if (options & VERBOSE)
         printf("%s: getaddrinfo failed with error {%s}\n",
                verbose_prompt.c_str(),gai_strerror(getaddrinfo_res));

      return -1;
   }

   ADDRINFO * curr = res;
   while (curr) {

      if (options & UDP)
         sock = socket(curr->ai_family,SOCK_DGRAM,0);
      else
         sock = socket(curr->ai_family,SOCK_STREAM,0);

      if (sock == INVALID_SOCKET) {

         if (options & VERBOSE)
            printf("%s: attempt to initialize socket failed with error %s\n",
                   verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

         goto finally;
      }

      if (curr->ai_family == AF_INET)
         ((SOCKADDR_IN *)curr->ai_addr)->sin_port = htons(port);
      else
         ((SOCKADDR_IN6 *)curr->ai_addr)->sin6_port = htons(port);

      if (options & VERBOSE) {

         char buf[INET6_ADDRSTRLEN];
         if (curr->ai_family == AF_INET)
            inet_ntop(AF_INET,&((SOCKADDR_IN *)curr->ai_addr)->sin_addr,buf,INET6_ADDRSTRLEN);
         else
            inet_ntop(AF_INET6,&((SOCKADDR_IN6 *)curr->ai_addr)->sin6_addr,buf,INET6_ADDRSTRLEN);

         printf("%s: attempting to connect to %s via the %s protocol\n",
                verbose_prompt.c_str(),buf,(curr->ai_family == AF_INET ? "IPv4" : "IPv6"));
      }

      int connect_res;
      connect_res = connect(sock,curr->ai_addr,curr->ai_addrlen);

      if (connect_res == SOCKET_ERROR) {

         if (options & VERBOSE)
            printf("%s: connection attempt failed with error %s\n",
                   verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

         closesocket(sock);
         sock = 0;

         curr = curr->ai_next;
         continue;
      }

      if (options & NONBLOCKING) {
         u_long yes = 1;
         if (ioctlsocket(sock,FIONBIO,&yes) == SOCKET_ERROR) {

            if (options & VERBOSE)
               printf("%s: attempt to configure socket as nonblocking failed with error %s\n",
                      verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

            goto finally;
         }
      }

      if (options & VERBOSE)
         printf("%s: connection attempt succeeded\n",verbose_prompt.c_str());

      if (options & NONBLOCKING) {
         u_long yes = 1;
         if (ioctlsocket(sock,FIONBIO,&yes) == SOCKET_ERROR) {

            if (options & VERBOSE)
               printf("%s: attempt to configure socket as nonblocking failed with error %s\n",
                      verbose_prompt.c_str(), WinOnly::print_sockerr().c_str());

            goto finally;
         }
      }

      protocol = curr->ai_family;
      retval = 0;
      is_live = true;

      if (curr->ai_family == AF_INET)
         memcpy(&this->addr.ipv4,curr->ai_addr,curr->ai_addrlen);
      else
         memcpy(&this->addr.ipv6,curr->ai_addr,curr->ai_addrlen);

      break;
   }

finally:
   freeaddrinfo(res);

   return retval;
}

int WiredLink::close() {
   protocol = AF_UNSPEC;
   ZeroMemory(&addr,sizeof(addr));
   shutdown(sock,SD_BOTH);
   int res = closesocket(sock);
   sock = 0;
   is_live = false;
   return res;
}

long WiredLink::send(const uint8_t * data, size_t len) {
   if (!sock)
      return -1;

retry:
   int res = ::send(sock,(char *)data,len,0);

   if (res == SOCKET_ERROR) {
      switch (WSAGetLastError()) {
         case WSAEINTR:
            goto retry;
            break;
         default:
            is_live = false;
            break;
      }
   }

   return res;
}

long WiredLink::recv(uint8_t * data, size_t len) {
   if (!sock || !is_live)
      return -1;

retry:
   int res = ::recv(sock,(char *)data,len,(options & NONBLOCKING) ? 0 : MSG_WAITALL);

   if (res == 0 && len != 0 && !(options & UDP))
      is_live = false;
   else if (res == SOCKET_ERROR) {
      switch (WSAGetLastError()) {
         case WSAEINTR:
            goto retry;
            break;
         case WSAEWOULDBLOCK:
            res = 0;
            break;
         default:
            break;
      }
   }

   return res;
}

bool WiredLink::live() {
   return is_live;
}

#elif defined(__unix__)

WiredLink::WiredLink(uint options, std::string verbose_prompt) 
   : options(options) {
      this->verbose_prompt = verbose_prompt;
      this->is_live = false;
}

WiredLink::~WiredLink() {
   if (sock)
      ::close(sock);
}

int WiredLink::open(std::string addr, uint port) {

   if (options & VERBOSE) {
      if (options & UDP)
         printf("%s: opening socket using UDP protocol\n",verbose_prompt.c_str());
      else
         printf("%s: opening socket using TCP protocol\n",verbose_prompt.c_str());

      if (options & NONBLOCKING)
         printf("%s: configuring socket in nonblocking mode\n",verbose_prompt.c_str());

      printf("%s: connecting to address %s at port %u\n",
             verbose_prompt.c_str(),addr.c_str(),port);
   }


   int retval = -1;

   struct addrinfo hints;
   bzero(&hints,sizeof(struct addrinfo));
   if (((options & IPV4) && (options & IPV6)) || !(options & (IPV4 | IPV6))) {

      if (options & VERBOSE)
         printf("%s: Attempting to collect suitable addresses for %s via protocol IPv4, IPv6\n",
                verbose_prompt.c_str(),addr.c_str());

      hints.ai_family = AF_UNSPEC;
   }
   else if (options & IPV4) {

      if (options & VERBOSE)
         printf("%s: Attempting to collect suitable addresses for %s via protocol IPv4\n",
                verbose_prompt.c_str(),addr.c_str());

      hints.ai_family = AF_INET;
   }
   else if (options & IPV6) {

      if (options & VERBOSE)
         printf("%s: Attempting to collect suitable addresses for %s via protocol IPv6\n",
                verbose_prompt.c_str(),addr.c_str());

      hints.ai_family = AF_INET6;
   }
   hints.ai_flags = AI_ADDRCONFIG;

   struct addrinfo * res;
   int getaddrinfo_res;
   if ( (getaddrinfo_res = getaddrinfo(addr.c_str(),NULL,&hints,&res)) != 0) {

      if (options & VERBOSE)
         printf("%s: getaddrinfo failed with error {%s}\n",
                verbose_prompt.c_str(),gai_strerror(getaddrinfo_res));

      return -1;
   }

   struct addrinfo * curr = res;
   while (curr) {

      if (options & UDP)
         sock = socket(curr->ai_family,SOCK_DGRAM,0);
      else
         sock = socket(curr->ai_family,SOCK_STREAM,0);

      if (sock == -1) {

         if (options & VERBOSE)
            printf("%s: attempt to initialize socket failed\n",verbose_prompt.c_str());

         goto finally;
      }

      if (curr->ai_family == AF_INET)
         ((struct sockaddr_in *)curr->ai_addr)->sin_port = htons(port);
      else
         ((struct sockaddr_in6 *)curr->ai_addr)->sin6_port = htons(port);

      if (options & VERBOSE) {

         char buf[INET6_ADDRSTRLEN];
         if (curr->ai_family == AF_INET)
            inet_ntop(AF_INET,&((struct sockaddr_in *)curr->ai_addr)->sin_addr,buf,INET6_ADDRSTRLEN);
         else
            inet_ntop(AF_INET6,&((struct sockaddr_in6 *)curr->ai_addr)->sin6_addr,buf,INET6_ADDRSTRLEN);

         printf("%s: attempting to connect to %s via the %s protocol\n",
                verbose_prompt.c_str(),buf,(curr->ai_family == AF_INET ? "IPv4" : "IPv6"));
      }

      int connect_res;
      connect_res = connect(sock,curr->ai_addr,curr->ai_addrlen);

      if (connect_res == -1) {

         if (options & VERBOSE)
            printf("%s: connection attempt failed\n",verbose_prompt.c_str());

         ::close(sock);
         sock = 0;

         curr = curr->ai_next;
         continue;
      }

      if (options & NONBLOCKING) {
         if (fcntl(sock,F_SETFL,fcntl(sock,F_GETFL) | O_NONBLOCK) == -1) {

            if (options & VERBOSE)
               printf("%s: attempt to configure socket as nonblocking failed\n",verbose_prompt.c_str());

            goto finally;
         }
      }

      if (options & VERBOSE)
         printf("%s: connection attempt succeeded\n",verbose_prompt.c_str());

      if (options & NONBLOCKING) {
         if (fcntl(sock,F_SETFL,fcntl(sock,F_GETFL) | O_NONBLOCK) == -1) {

            if (options & VERBOSE)
               printf("%s: attempt to configure socket as nonblocking failed\n",verbose_prompt.c_str());

            goto finally;
         }
      }

      protocol = curr->ai_family;
      retval = 0;
      is_live = true;

      if (curr->ai_family == AF_INET)
         memcpy(&this->addr.ipv4,curr->ai_addr,curr->ai_addrlen);
      else
         memcpy(&this->addr.ipv6,curr->ai_addr,curr->ai_addrlen);

      break;
   }

finally:
   freeaddrinfo(res);

   return retval;
}

int WiredLink::close() {
   protocol = AF_UNSPEC;
   bzero(&addr,sizeof(addr));
   int res = ::close(sock);
   sock = 0;
   is_live = false;
   return res;
}

long WiredLink::send(const uint8_t * data, size_t len) {
   if (!sock)
      return -1;

retry:
   int res = ::send(sock,data,len,MSG_NOSIGNAL);

   if (res == -1) {
      switch (errno) {
         case EINTR:
            goto retry;
            break;
         case ECONNRESET:
         case EPIPE:
         case EBADF:
            is_live = false;
            break;
      }
   }

   return res;
}

long WiredLink::recv(uint8_t * data, size_t len) {
   if (!sock || !is_live)
      return -1;

retry:
   int res = ::recv(sock,data,len,MSG_WAITALL);

   if (res == 0 && len != 0 && !(options & UDP))
      is_live = false;
   else if (res == -1 && errno == EINTR)
      goto retry;
#if EAGAIN == EWOULDBLOCK
   else if (res == -1 && errno == EAGAIN)
#else
   else if (res == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
#endif
      res = 0;

   return res;
}

bool WiredLink::live() {
   return is_live;
}

#endif

}
