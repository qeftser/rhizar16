
#ifndef __RHIZAR16_WIRED_MISC__

#define __RHIZAR16_WIRED_MISC__
#include <string>

namespace Rhizar16 {

namespace Wired {

   /* return true if the passed identifier matches
    * the hostname or ip address (v4 or v6) of
    * the current machine.                        */
   bool is_self(std::string id);

};

};

#endif
