
#ifndef __RHIZAR16_PRINT_SOCKERR__

#define __RHIZAR16_PRINT_SOCKERR__

#ifdef _WIN32
#include <string>
#include <windows.h>
#include <winnt.h>

namespace Rhizar16 {

extern int __RHIZAR16_WSASTARTUP_CALLED__;

class WinOnly {
public:

   static std::string print_sockerr() {
      LPWORD lpMsgBuf;
      DWORD dw = WSAGetLastError();

      if (FormatMessage(
               FORMAT_MESSAGE_ALLOCATE_BUFFER |
               FORMAT_MESSAGE_FROM_SYSTEM |
               FORMAT_MESSAGE_IGNORE_INSERTS,
               NULL,
               dw,
               MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
               (LPTSTR) &lpMsgBuf,
               0, NULL) == 0) {
         return std::string("unknown");
      }

      std::string res = std::string((LPTSTR)lpMsgBuf);
      LocalFree(lpMsgBuf);
      return res;
   }
};

}

#endif

#endif
