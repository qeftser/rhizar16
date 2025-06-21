
#include "wired_misc.h"

#ifdef _WIN32

#include "wired_windows_support.h"

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <winsock.h>
#include <windows.h>
#include <ws2def.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#elif defined(__unix__)

#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

#endif

namespace Rhizar16 {

namespace Wired {

#ifdef _WIN32

bool is_self(std::string id) {

   if (__RHIZAR16_WSASTARTUP_CALLED__ == 0) {
      WSADATA wsa_data;
      WSAStartup(MAKEWORD(2,2),&wsa_data);
      __RHIZAR16_WSASTARTUP_CALLED__ = 1;
   }

   /* first check the hostname - on windows it can be longer than unix */
   char * hostname_str = (char *)malloc(sizeof(char) * 257);
   gethostname(hostname_str,257);
   std::string hostname(hostname_str);
   free(hostname_str);

   if (hostname == id)
      return true;

   /* proceed to the addrs... */

   /* from example... */
   size_t buf_size = 0;
   int gaa_retval = 0;
   IP_ADAPTER_ADDRESSES * addrs = NULL;

   GetAdaptersAddresses(AF_UNSPEC,0,NULL,addrs,&buf_size);

   addrs = (IP_ADAPTER_ADDRESSES *)malloc(buf_size);

   gaa_retval = GetAdaptersAddresses(AF_UNSPEC,0,NULL,addrs,&buf_size);

   if (gaa_reval != ERROR_SUCCESS)
      return false;

   bool retval = false;

   IP_ADAPTER_ADDRESSES * curr = addrs;

   while (curr) {

      PIP_ADAPTER_UNICAST_ADDRESS_LH curr_sockaddr = curr->FirstUnicastAddress;

      while (curr_sockaddr) {

         if (curr_sockaddr->Address.lpSockaddr->sa_family == AF_INET) {

            struct sockaddr_in * ipv4_addr = curr_sockaddr->Address->lpSockaddr;
            char * addr_str = (char *)malloc(sizeof(char) * INET_ADDRSTRLEN);
            inet_ntop(AF_INET,&ipv4_addr->sin_addr.s_addr,addr_str,INET_ADDRSTRLEN);
            std::string addr(addr_str);
            free(addr_str);

            if (addr == id)
               retval = true;

         }
         else if (curr_sockaddr->Address.lpSockaddr->sa_family == AF_INET6) {

            struct sockaddr_in6 * ipv6_addr = curr_sockaddr->Address->lpSockaddr;
            char * addr_str = (char *)malloc(sizeof(char) * INET6_ADDRSTRLEN);
            inet_ntop(AF_INET6,&ipv6_addr->sin_addr.s_addr,addr_str,INET6_ADDRSTRLEN);
            std::string addr(addr_str);
            free(addr_str);

            if (addr == id)
               retval = true;

         }

         curr_sockaddr = curr_sockaddr->next;
      }

      curr = curr->Next;
   }

   free(addrs);

   return retval;

}

#elif defined(__unix__)

bool is_self(std::string id) {

   /* first we check the system hostname */

   char * hostname_str = (char *)malloc(sizeof(char) * HOST_NAME_MAX + 1);
   gethostname(hostname_str,HOST_NAME_MAX + 1);
   std::string hostname(hostname_str);
   free(hostname_str);

   if (hostname == id)
      return true;

   /* now we have to collect our ip addresses 
    * for each device and check these.        */

   struct ifaddrs * addrs;
   if (-1 == getifaddrs(&addrs))
      return false;

   bool retval = false;

   struct ifaddrs * curr = addrs;

   while (curr) {

      if (curr->ifa_addr->sa_family == AF_INET) {

         struct sockaddr_in * ipv4_addr = (struct sockaddr_in *)curr->ifa_addr;
         char * addr_str = (char *)malloc(sizeof(char) * INET_ADDRSTRLEN);
         inet_ntop(AF_INET,&ipv4_addr->sin_addr.s_addr,addr_str,INET_ADDRSTRLEN);
         std::string addr(addr_str);
         free(addr_str);

         if (addr == id)
            retval = true;

      }
      else if (curr->ifa_addr->sa_family == AF_INET6) {

         struct sockaddr_in6 * ipv6_addr = (struct sockaddr_in6 *)curr->ifa_addr;
         char * addr_str = (char *)malloc(sizeof(char) * INET6_ADDRSTRLEN);
         inet_ntop(AF_INET6,&ipv6_addr->sin6_addr.s6_addr,addr_str,INET6_ADDRSTRLEN);
         std::string addr(addr_str);
         free(addr_str);

         if (addr == id)
            retval = true;

      }

      curr = curr->ifa_next;
   }

   freeifaddrs(addrs);

   return retval;
}

#endif

}

}
