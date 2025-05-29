
#ifndef __RHIZAR16_UTILS__

#define __RHIZAR16_UTILS__

#include <stdint.h>
#include <stdio.h>

namespace Rhizar16 {

/* print an error statement */
template<typename ... Args>
void RHIZAR16_ERROR(char * str, Args&&... args) {
   fprintf(stderr,"\033[31m[RHIZAR16] ERROR: ");
   fprintf(stderr,str,args...);
   fprintf(stderr,"\033[0m");
}

template<typename ... Args>
void RHIZAR16_WARN(char * str, Args&&... args) {
   fprintf(stderr,"\033[33m[RHIZAR16] WARN : ");
   fprintf(stderr,str,args...);
   fprintf(stderr,"\033[0m");
}

/* return a bitmask of length n bits */
uint64_t bitmask(int n);

/* print the logo xD */
void print_logo();

}

#endif
