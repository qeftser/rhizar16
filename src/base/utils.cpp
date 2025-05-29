
#include "utils.h"

namespace Rhizar16 {

uint64_t bitmask(int n) {
   switch (n) {
      case 0:
         return 0x0000000000000000;
      case 1:
         return 0x0000000000000001;
      case 2:
         return 0x0000000000000003;
      case 3:
         return 0x0000000000000007;
      case 4:
         return 0x000000000000000f;
      case 5:
         return 0x000000000000001f;
      case 6:
         return 0x000000000000003f;
      case 7:
         return 0x000000000000007f;
      case 8:
         return 0x00000000000000ff;
      case 9:
         return 0x00000000000001ff;
      case 10:
         return 0x00000000000003ff;
      case 11:
         return 0x00000000000007ff;
      case 12:
         return 0x0000000000000fff;
      case 13:
         return 0x0000000000001fff;
      case 14:
         return 0x0000000000003fff;
      case 15:
         return 0x0000000000007fff;
      case 16:
         return 0x000000000000ffff;
      case 17:
         return 0x000000000001ffff;
      case 18:
         return 0x000000000003ffff;
      case 19:
         return 0x000000000007ffff;
      case 20:
         return 0x00000000000fffff;
      case 21:
         return 0x00000000001fffff;
      case 22:
         return 0x00000000003fffff;
      case 23:
         return 0x00000000007fffff;
      case 24:
         return 0x0000000000ffffff;
      case 25:
         return 0x0000000001ffffff;
      case 26:
         return 0x0000000003ffffff;
      case 27:
         return 0x0000000007ffffff;
      case 28:
         return 0x000000000fffffff;
      case 29:
         return 0x000000001fffffff;
      case 30:
         return 0x000000003fffffff;
      case 31:
         return 0x000000007fffffff;
      case 32:
         return 0x00000000ffffffff;
      case 33:
         return 0x00000001ffffffff;
      case 34:
         return 0x00000003ffffffff;
      case 35:
         return 0x00000007ffffffff;
      case 36:
         return 0x0000000fffffffff;
      case 37:
         return 0x0000001fffffffff;
      case 38:
         return 0x0000003fffffffff;
      case 39:
         return 0x0000007fffffffff;
      case 40:
         return 0x000000ffffffffff;
      case 41:
         return 0x000001ffffffffff;
      case 42:
         return 0x000003ffffffffff;
      case 43:
         return 0x000007ffffffffff;
      case 44:
         return 0x00000fffffffffff;
      case 45:
         return 0x00001fffffffffff;
      case 46:
         return 0x00003fffffffffff;
      case 47:
         return 0x00007fffffffffff;
      case 48:
         return 0x0000ffffffffffff;
      case 49:
         return 0x0001ffffffffffff;
      case 50:
         return 0x0003ffffffffffff;
      case 51:
         return 0x0007ffffffffffff;
      case 52:
         return 0x000fffffffffffff;
      case 53:
         return 0x001fffffffffffff;
      case 54:
         return 0x003fffffffffffff;
      case 55:
         return 0x007fffffffffffff;
      case 56:
         return 0x00ffffffffffffff;
      case 57:
         return 0x01ffffffffffffff;
      case 58:
         return 0x03ffffffffffffff;
      case 59:
         return 0x07ffffffffffffff;
      case 60:
         return 0x0fffffffffffffff;
      case 61:
         return 0x1fffffffffffffff;
      case 62:
         return 0x3fffffffffffffff;
      case 63:
         return 0x7fffffffffffffff;
      default:
         return 0xffffffffffffffff;
   }
}

void print_logo() {

   printf("\033[31m░▒▓███████▓▒░ \033[90m  ░▒▓█▓▒░░▒▓███████▓▒░ \n");
   printf("\033[31m░▒▓█▓▒░░▒▓█▓▒░\033[90m▒▓████▓▒░▒▓█▓▒░        \n");
   printf("\033[31m░▒▓█▓▒░░▒▓█▓▒░\033[90m  ░▒▓█▓▒░▒▓█▓▒░        \n");
   printf("\033[31m░▒▓███████▓▒░ \033[90m  ░▒▓█▓▒░▒▓███████▓▒░  \n");
   printf("\033[31m░▒▓█▓▒░░▒▓█▓▒░\033[90m  ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n");
   printf("\033[31m░▒▓█▓▒░░▒▓█▓▒░\033[90m  ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n");
   printf("\033[31m░▒▓█▓▒░░▒▓█▓▒░\033[90m  ░▒▓█▓▒░░▒▓██████▓▒░  \n");
   printf(" I will continue when you are gone\033[0m\n");

}
                                     
}

