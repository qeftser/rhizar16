
#include "wired_test.h"
#include "wired_link.h"
#include "wired_server.h"
#include <stdlib.h>
#include <algorithm>
#include <condition_variable>

namespace Rhizar16 {

namespace TestWired {

#ifdef _WIN32
#include <windows.h>
#include <bcrypt.h>
#include <stdint.h>
uint32_t arc4random() {
   uint32_t retval;
   BCryptGenRandom(NULL, (uint8_t *)&retval, sizeof(retval), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
   return retval;
}
#endif


int wired_link_initialization_0() {
   WiredLink l;

   return 1;
}

int wired_link_initialization_1() {
   WiredLink l(WiredLink::Option::IPV4 | WiredLink::Option::NONBLOCKING);

   return 1;
}

int wired_link_initialization_2() {
   WiredLink l(WiredLink::Option::IPV4 | WiredLink::Option::UDP,
               "a prompt for verbose mode");

   return 1;
}

int wired_server_initialization_0() {
   WiredServer s;

   return 1;
}

int wired_server_initialization_1() {
   WiredServer s(1);

   return 1;
}

int wired_server_initialization_2() {
   WiredServer s(1, "a prompt for verbose mode");

   return 1;
}

int wired_link_open_0() {
   WiredLink l;

   int retval = 1;

   if (l.open("localhost",(arc4random()%40000)+10000) != -1)
      retval = 0;

   return retval;
}

int wired_link_open_1() {
   WiredLink l(WiredLink::Option::NONBLOCKING);

   int retval = 1;

   if (l.open("localhost",(arc4random()%40000)+10000) != -1)
      retval = 0;

   return retval;
}

int wired_link_open_2() {
   WiredLink l(WiredLink::Option::UDP);

   int retval = 1;

   if (l.open("localhost",(arc4random()%40000)+10000) != 0)
      retval = 0;

   return retval;
}

int wired_link_open_3() {
   WiredLink l(WiredLink::Option::UDP|WiredLink::Option::IPV4);

   int retval = 1;

   if (l.open("localhost",(arc4random()%40000)+10000) != 0)
      retval = 0;

   return retval;
}

int wired_link_open_4() {
   WiredLink l(WiredLink::Option::UDP|WiredLink::Option::IPV6);

   int retval = 1;

   if (l.open("localhost",(arc4random()%40000)+10000) != 0)
      retval = 0;

   return retval;
}

int wired_link_open_5() {
   WiredLink l(WiredLink::Option::UDP|WiredLink::Option::NONBLOCKING);

   int retval = 1;

   if (l.open("localhost",(arc4random()%40000)+10000) != 0)
      retval = 0;

   return retval;
}

int wired_server_start_0() {
   WiredServer s;

   int retval = 1;

   if (s.start((arc4random()%40000)+10000) != 0)
      retval = 0;

   return retval;
}

int wired_server_start_1() {
   WiredServer s;

   int retval = 1;

   if (s.start((arc4random()%40000)+10000) != 0)
      retval = 0;

   if (s.start((arc4random()%40000)+10000) != 0)
      retval = 0;

   return retval;
}

int wired_server_start_2() {
   WiredServer s;

   int retval = 1;

   if (s.start((arc4random()%40000)+10000) != 0)
      retval = 0;

   s.finish();

   if (s.start((arc4random()%40000)+10000) != 0)
      retval = 0;

   s.finish();

   if (s.start((arc4random()%40000)+10000) != 0)
      retval = 0;

   return retval;
}

int wired_link_close_0() {

   WiredLink l(WiredLink::Option::UDP);

   int retval = 1;

   if (l.open("localhost",((arc4random()%40000)+10000)) != 0)
      retval = 0;

   if (l.close() != 0)
      retval = 0;

   return retval;
}

int wired_link_close_1() {

   WiredLink l(WiredLink::Option::UDP);

   int retval = 1;

   if (l.open("localhost",((arc4random()%40000)+10000)) != 0)
      retval = 0;

   if (l.close() != 0)
      retval = 0;

   if (l.open("localhost",((arc4random()%40000)+10000)) != 0)
      retval = 0;

   if (l.close() != 0)
      retval = 0;

   return retval;
}

int wired_link_close_2() {

   WiredLink l(WiredLink::Option::UDP);

   int retval = 1;

   if (l.open("localhost",((arc4random()%40000)+10000)) != 0)
      retval = 0;

   if (l.close() != 0)
      retval = 0;

   if (l.open("localhost",((arc4random()%40000)+10000)) != 0)
      retval = 0;

   if (l.close() != 0)
      retval = 0;

   if (l.open("localhost",((arc4random()%40000)+10000)) != 0)
      retval = 0;

   if (l.close() != 0)
      retval = 0;

   return retval;
}

int wired_connect_0() {
   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);

   int retval = 1;

   if (l.open("localhost",port) != 0)
      retval = 0;

   return retval;
}

int wired_connect_1() {
   WiredLink l(WiredLink::Option::IPV4);
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);

   int retval = 1;

   if (l.open("localhost",port) != 0)
      retval = 0;

   return retval;
}

int wired_connect_2() {
   WiredLink l(WiredLink::Option::IPV6);
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);

   int retval = 1;

   if (l.open("localhost",port) != 0)
      retval = 0;

   return retval;
}

int wired_connect_3() {
   WiredLink l[10] = {
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                     };
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);

   int retval = 1;

   if (l[0].open("localhost",port) != 0)
      retval = 0;
   if (l[1].open("localhost",port) != 0)
      retval = 0;
   if (l[2].open("localhost",port) != 0)
      retval = 0;
   if (l[3].open("localhost",port) != 0)
      retval = 0;
   if (l[4].open("localhost",port) != 0)
      retval = 0;
   if (l[5].open("localhost",port) != 0)
      retval = 0;
   if (l[6].open("localhost",port) != 0)
      retval = 0;
   if (l[7].open("localhost",port) != 0)
      retval = 0;
   if (l[8].open("localhost",port) != 0)
      retval = 0;
   if (l[9].open("localhost",port) != 0)
      retval = 0;

   return retval;
}

int wired_connect_4() {
   WiredLink l[10] = {
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                     };
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);

   int retval = 1;

   if (l[0].open("localhost",port) != 0)
      retval = 0;
   if (l[1].open("localhost",port) != 0)
      retval = 0;
   if (l[2].open("localhost",port) != 0)
      retval = 0;
   if (l[3].open("localhost",port) != 0)
      retval = 0;
   if (l[4].open("localhost",port) != 0)
      retval = 0;
   if (l[5].open("localhost",port) != 0)
      retval = 0;
   if (l[6].open("localhost",port) != 0)
      retval = 0;
   if (l[7].open("localhost",port) != 0)
      retval = 0;
   if (l[8].open("localhost",port) != 0)
      retval = 0;
   if (l[9].open("localhost",port) != 0)
      retval = 0;

   return retval;
}

int wired_connect_5() {
   WiredLink l4[10] = {
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                        WiredLink::Option::IPV4, 
                      };
   WiredLink l6[10] = {
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                        WiredLink::Option::IPV6, 
                      };
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);

   int retval = 1;

   for (int i = 0; i < 10; ++i) {

      if (l4[i].open("localhost",port) != 0)
         retval = 0;
      if (l6[i].open("localhost",port) != 0)
         retval = 0;
   }

   return retval;
}

int wired_link_close_3() {
   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);

   int retval = 1;

   if (l.open("localhost",port) != 0)
      retval = 0;

   if (l.close() != 0)
      retval = 0;

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   return retval;
}

int wired_link_close_4() {
   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);

   int retval = 1;

   if (l.open("localhost",port) != 0)
      retval = 0;

   if (l.close() != 0)
      retval = 0;

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   if (l.open("localhost",port) != 0)
      retval = 0;

   if (l.close() != 0)
      retval = 0;

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   return retval;
}

int wired_link_close_5() {
   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);

   int retval = 1;

   for (int i = 0; i < 20; ++i) {
      if (l.open("localhost",port) != 0)
         retval = 0;

      if (l.close() != 0)
         retval = 0;

      std::this_thread::sleep_for(std::chrono::milliseconds(1));
   }

   return retval;
}

int wired_link_close_6() {

   WiredLink l[100];
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);

   int retval = 1;

   for (int i = 0; i < 100; ++i) {
      if (l[i].open("localhost",port) != 0)
         retval = 0;
   }
   for (int i = 0; i < 100; ++i) {
      if (l[i].close() != 0)
         retval = 0;
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
   }

   return retval;
}

int wired_link_send_0() {

   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);
   l.open("localhost",port);

   int retval = 1;

   int data = 5;
   if (l.send((uint8_t*)&data,sizeof(int)) != sizeof(int))
      retval = 0;

   return retval;
}

int wired_link_send_1() {

   WiredLink l1(WiredLink::Option::UDP);
   WiredLink l2(WiredLink::Option::UDP);

   uint port = ((arc4random()%40000)+10000);

   l1.open("localhost",port);
   l2.open("localhost",port);

   int retval = 1;

   int data = 5;
   if (l1.send((uint8_t*)&data,sizeof(int)) != sizeof(int))
      retval = 0;

   return retval;
}

int wired_link_send_2() {

   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);

   s.start(port);
   l.open("localhost",port);
   s.finish();

   std::this_thread::yield();

   int retval = 1;

   int data = 5;
   l.send((uint8_t *)&data,sizeof(int));
   if (l.send((uint8_t *)&data,sizeof(int)) != -1)
      retval = 0;

   return retval;
}

int wired_link_is_live_0() {
   WiredLink l;

   int retval = 1;

   if (l.live() == true)
      retval = 0;

   return retval;
}

int wired_link_is_live_1() {
   WiredLink l(WiredLink::Option::UDP);

   uint port = ((arc4random()%40000)+10000);
   l.open("localhost",port);

   int retval = 1;

   if (l.live() == false)
      retval = 0;

   return retval;
}

int wired_link_is_live_2() {
   WiredLink l(WiredLink::Option::UDP);

   uint port = ((arc4random()%40000)+10000);
   l.open("localhost",port);
   l.close();

   int retval = 1;

   if (l.live() == true)
      retval = 0;

   return retval;
}

int wired_link_is_live_3() {
   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   int retval = 1;

   if (l.live() == false)
      retval = 0;

   return retval;
}

int wired_link_is_live_4() {
   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);
   l.close();

   int retval = 1;

   if (l.live() == true)
      retval = 0;

   return retval;
}

int wired_link_is_live_5() {
   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);
   s.finish();

   int retval = 1;

   l.send((uint8_t *)&retval,sizeof(int));
   l.send((uint8_t *)&retval,sizeof(int));

   if (l.live() == true)
      retval = 0;

   return retval;
}

int wired_link_is_live_6() {
   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);
   s.finish();

   int retval = 1;

   l.recv(NULL,0);

   if (l.live() == false)
      retval = 0;

   return retval;
}

int wired_link_is_live_7() {
   WiredLink l;
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);
   s.finish();

   int retval = 1;

   l.recv((uint8_t *)&retval,1);

   if (l.live() == true)
      retval = 0;

   return retval;
}

int wired_server_get_ready_0() {
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   std::vector<WiredServer::socktype> col;

   int retval = 1;

   if (s.get_ready(col) != 0)
      retval = 0;

   if (col.size() != 0)
      retval = 0;

   return retval;
}

int wired_server_get_ready_1() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   std::vector<WiredServer::socktype> col;

   int retval = 1;

   if (s.get_ready(col) != 1)
      retval = 0;

   if (col.size() != 1)
      retval = 0;

   return retval;
}

int wired_server_get_ready_2() {
   WiredServer s;
   WiredLink l[10];

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   for (int i = 0; i < 10; ++i)
      l[i].open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   std::vector<WiredServer::socktype> col;

   int retval = 1;

   if (s.get_ready(col) != 10)
      retval = 0;

   if (col.size() != 10)
      retval = 0;

   return retval;
}

void wired_test_delay_open(WiredLink * l, uint port) {

   std::this_thread::yield();
   std::this_thread::sleep_for(std::chrono::milliseconds(200));

   l->open("localhost",port);

   return;
}

int wired_server_wait_ready_0() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::vector<WiredServer::socktype> col;

   int retval = 1;

   if (s.wait_ready(col,std::chrono::milliseconds(100)) != 1)
      retval = 0;

   if (col.size() != 1)
      retval = 0;

   return retval;
}

int wired_server_wait_ready_1() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   std::vector<WiredServer::socktype> col;

   std::thread d0(wired_test_delay_open,&l,port);

   int retval = 1;

   if (s.wait_ready(col,std::chrono::milliseconds(100)) != 1)
      retval = 0;

   if (col.size() != 1)
      retval = 0;

   d0.join();

   return retval;
}

int wired_server_get_ready_3() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   std::vector<WiredServer::socktype> col;

   std::thread d0(wired_test_delay_open,&l,port);

   int retval = 1;

   if (s.get_ready(col) != 0)
      retval = 0;

   if (col.size() != 0)
      retval = 0;

   d0.join();

   return retval;
}

int wired_server_wait_ready_2() {
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   std::vector<WiredServer::socktype> col;

   int retval = 1;

   if (s.wait_ready(col,std::chrono::milliseconds(1)) != 0)
      retval = 0;

   if (col.size() != 0)
      retval = 0;

   return retval;
}

int wired_server_wait_ready_3() {
   WiredServer s;
   WiredLink l0;
   WiredLink l1;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   std::vector<WiredServer::socktype> col;

   std::thread d0(wired_test_delay_open,&l0,port);
   std::this_thread::sleep_for(std::chrono::milliseconds(3));
   std::thread d1(wired_test_delay_open,&l1,port);

   int retval = 1;

   if (s.wait_ready(col,std::chrono::milliseconds(100)) != 1)
      retval = 0;

   if (col.size() != 1)
      retval = 0;

   d0.join();
   d1.join();

   return retval;
}

int wired_server_get_closed_0() {
   WiredServer s;

   std::vector<WiredServer::socktype> col;

   int retval = 1;

   if (s.get_closed(col) != 0)
      retval = 0;

   if (col.size() != 0)
      retval = 0;

   return retval;
}

int wired_server_get_closed_1() {
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   std::vector<WiredServer::socktype> col;

   int retval = 1;

   if (s.get_closed(col) != 0)
      retval = 0;

   if (col.size() != 0)
      retval = 0;

   return retval;
}

int wired_server_get_closed_2() {
   WiredServer s;
   WiredLink l[10];

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   for (int i = 0; i < 10; ++i)
      l[i].open("localhost",port);

   std::vector<WiredServer::socktype> col;

   int retval = 1;

   if (s.get_closed(col) != 0)
      retval = 0;

   if (col.size() != 0)
      retval = 0;

   return retval;
}

int wired_server_get_closed_3() {
   /* this is done due to the windows socket close procedure
    * being implimented differently that the unix/linux one */
#ifdef _WIN32
   return 2;
#endif

   WiredServer s;
   WiredLink l[10];

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   for (int i = 0; i < 10; ++i)
      l[i].open("localhost",port);

   for (int i = 0; i < 10; ++i)
      l[i].close();

   std::this_thread::sleep_for(std::chrono::milliseconds(10));

   std::vector<WiredServer::socktype> col;

   int retval = 1;

   if (s.get_closed(col) != 10)
      retval = 0;

   if (col.size() != 10)
      retval = 0;

   return retval;
}

int wired_server_clean_0() {
   WiredServer s;

   int retval = 1;

   if (s.clean() != 0)
      retval = 0;

   return retval;
}

int wired_server_clean_1() {
   WiredServer s;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   int retval = 1;

   if (s.clean() != 0)
      retval = 0;

   return retval;
}

int wired_server_clean_2() {
   WiredServer s;
   WiredLink l[10];

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   for (int i = 0; i < 10; ++i)
      l[i].open("localhost",port);

   int retval = 1;

   if (s.clean() != 0)
      retval = 0;

   return retval;
}

int wired_server_clean_3() {
   /* this is done due to the windows socket close procedure
    * being implimented differently that the unix/linux one */
#ifdef _WIN32
   return 2;
#endif

   WiredServer s;
   WiredLink l[10];

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   for (int i = 0; i < 10; ++i)
      l[i].open("localhost",port);

   for (int i = 0; i < 10; ++i)
      l[i].close();

   std::this_thread::sleep_for(std::chrono::milliseconds(10));

   int retval = 1;

   if (s.clean() != 10)
      retval = 0;

   return retval;
}

int wired_server_clean_4() {
   WiredServer s;
   WiredLink l[10];

   uint port = ((arc4random()%40000)+10000);
   s.start(port);

   for (int i = 0; i < 10; ++i)
      l[i].open("localhost",port);

   std::vector<WiredServer::socktype> col;

   std::this_thread::sleep_for(std::chrono::milliseconds(3));

   s.wait_ready(col,std::chrono::milliseconds(10));

   for (WiredServer::socktype & sock : col)
      s.close(sock);

   int retval = 1;

   if (s.clean() != 10)
      retval = 0;

   return retval;
}

int wired_server_close_0() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   std::vector<WiredServer::socktype> col;

   s.wait_ready(col,std::chrono::milliseconds(3));
   s.close(col[0]);
   col.clear();
   l.recv((uint8_t *)&port,1);

   int retval = 1;

   if (s.get_closed(col) != 1)
      retval = 0;

   if (l.live() != false)
      retval = 0;

   return retval;
}

int wired_server_close_1() {
   WiredServer s;
   WiredLink l[10];

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   for (int i = 0; i < 10; ++i)
      l[i].open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   std::vector<WiredServer::socktype> col;

   s.get_ready(col);
   for (WiredServer::socktype sock : col)
      s.close(sock);
   col.clear();
   for (int i = 0; i < 10; ++i)
      l[i].recv((uint8_t *)&port,1);

   int retval = 1;

   if (s.get_closed(col) != 10)
      retval = 0;

   for (int i = 0; i < 10; ++i)
      if (l[i].live() != false)
         retval = 0;

   return retval;
}

int wired_server_recv_0() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   std::vector<WiredServer::socktype> col;

   s.wait_ready(col,std::chrono::milliseconds(10));

   int retval = 1;

   if (col.size() != 1)
      retval = 0;

   WiredServer::socktype conn = col[0];

   int value_recv = 0, value_send = 0xffffffff;
   s.recv(conn,(uint8_t *)&value_recv,sizeof(int));

   col.clear();

   if (s.get_ready(col) != 0)
      retval = 0;

   l.send((uint8_t *)&value_send,sizeof(int));

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   if (s.wait_ready(col,std::chrono::milliseconds(5)) != 1)
      retval = 0;

   if (value_recv != value_send)
      retval = 0;

   return retval;
}

int wired_server_recv_1() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   std::vector<WiredServer::socktype> col;

   s.wait_ready(col,std::chrono::milliseconds(10));

   int retval = 1;

   if (col.size() != 1)
      retval = 0;

   WiredServer::socktype conn = col[0];

   int value_recv[100], value_send[100];

   memset(&value_recv,0x00,sizeof(value_recv));
   memset(&value_send,0xff,sizeof(value_send));

   s.recv(conn,(uint8_t *)&value_recv,sizeof(value_recv));

   col.clear();

   if (s.get_ready(col) != 0)
      retval = 0;

   l.send((uint8_t *)&value_send,sizeof(value_send));

   std::this_thread::sleep_for(std::chrono::milliseconds(1));

   if (s.wait_ready(col,std::chrono::milliseconds(5)) != 1)
      retval = 0;

   if (memcmp(&value_send,&value_recv,sizeof(value_send) != 0))
      retval = 0;

   return retval;
}

void wired_test_send_data(WiredLink * l, uint8_t * data, uint len, int * go) {
   while (!(*go)) std::this_thread::yield();
   l->send(data,len);
}

int wired_server_recv_2() {

   int to_send_byte = 10000000;
   int threads = 4;

   WiredServer s;
   WiredLink l[threads];

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   for (int i = 0; i < threads; ++i)
      l[i].open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(10));

   std::vector<WiredServer::socktype> col;

   for (int i = 0; i < 10; ++i) {
      col.clear();
      if (s.get_ready(col) == threads)
         break;
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
   }

   int retval = 1;

   if (col.size() != threads)
      retval = 0;

   uint8_t * tosend[threads];
   uint8_t * torecv[threads];
   std::thread th[threads];

   std::sort(col.begin(),col.end());

   for (int i = 0; i < threads; ++i) {
      torecv[i] = (uint8_t *)malloc(to_send_byte);
      memset(torecv[i],0,to_send_byte);
      s.recv(col[i],torecv[i],to_send_byte);
   }

   for (int i = 0; i < threads; ++i) {
      tosend[i] = (uint8_t *)malloc(to_send_byte);
      /* we unfortunately have to reduce the quality of our
       * testing on windows, as the underlying system allocates
       * sockets seemingly randomly and there is no good way
       * to order them.                                      */
#ifdef _WIN32
      memset(tosend[i],0xff,to_send_byte);
#else
      memset(tosend[i],i,to_send_byte);
#endif
   }

   int go = 0;

   for (int i = 0; i < threads; ++i)
      th[i] = std::thread(&wired_test_send_data,&l[i],tosend[i],to_send_byte,&go);

   std::this_thread::sleep_for(std::chrono::milliseconds(threads));

   go = 1;

   int retries = 20;
   col.clear();
   while (s.get_ready(col) != threads && retries--) { 
      col.clear(); std::this_thread::sleep_for(std::chrono::milliseconds(10));
   }

   for (int i = 0; i < threads; ++i)
      if (memcmp(tosend[i],torecv[i],to_send_byte) != 0)
         retval = 0;

   for (int i = 0; i < threads; ++i) {
      if (th[i].joinable())
         th[i].join();
      free(tosend[i]);
      free(torecv[i]);
   }

   return retval;
}

int wired_server_recv_3() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(3));

   std::vector<WiredServer::socktype> col;

   s.wait_ready(col,std::chrono::milliseconds(3));

   int retval = 1;

   if (s.recv(col[0],(uint8_t *)&port,sizeof(int)) != 0)
      retval = 0;

   return retval;
}

int wired_server_recv_4() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(3));

   std::vector<WiredServer::socktype> col;

   s.wait_ready(col,std::chrono::milliseconds(3));

   s.recv(col[0],(uint8_t *)&port,sizeof(int));

   int retval = 1;

   if (s.recv(col[0],(uint8_t *)&retval,sizeof(int)) != -1)
      retval = 0;

   return retval;
}

int wired_server_recv_5() {
   WiredServer s;

   int retval = 1;

   if (s.recv(20,(uint8_t *)&retval,sizeof(int)) != -1)
      retval = 0;

   return retval;
}

int wired_server_recv_6() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(3));

   int retval = 1;

   if (s.recv(20,(uint8_t *)&retval,sizeof(int)) != -1)
      retval = 0;

   return retval;
}

int wired_server_send_link_recv_0() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(3));

   int retval = 1;

   int to_send = 0xffffffff, to_recv = 0;

   std::vector<WiredServer::socktype> col;

   s.wait_ready(col,std::chrono::milliseconds(3));

   if (s.send(col[0],(uint8_t *)&to_send,sizeof(int)) != 0)
      retval = 0;

   if (l.recv((uint8_t *)&to_recv,sizeof(int)) != sizeof(int))
      retval = 0;

   if (to_send != to_recv)
      retval = 0;

   return retval;
}

int wired_server_send_link_recv_1() {
   WiredServer s;
   WiredLink l(WiredLink::Option::NONBLOCKING);

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(3));

   int to_recv = 0xffffffff;

   int retval = 1;

   int res;
   if ((res = l.recv((uint8_t *)&to_recv,sizeof(int))) != 0)
      retval = 0;

   return retval;
}

int wired_server_send_link_recv_2() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(3));

   s.finish();

   std::this_thread::sleep_for(std::chrono::milliseconds(3));

   int to_recv = 0;

   int retval = 1;

   if (l.recv((uint8_t *)&to_recv,sizeof(int)) != 0)
      retval = 0;

   if (l.recv((uint8_t *)&to_recv,sizeof(int)) != -1)
      retval = 0;

   return retval;
}

int wired_server_send_link_recv_3() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(3));

   int retval = 1;

   int to_send[100], to_recv[100];
   memset(to_send,0xff,sizeof(to_send));
   memset(to_recv,0x00,sizeof(to_recv));

   std::vector<WiredServer::socktype> col;

   s.wait_ready(col,std::chrono::milliseconds(3));

   if (s.send(col[0],(uint8_t *)to_send,sizeof(to_send)) != 0)
      retval = 0;

   if (l.recv((uint8_t *)&to_recv,sizeof(to_send)) != sizeof(to_send))
      retval = 0;

   if (memcmp(to_send,to_recv,sizeof(to_send)) != 0)
      retval = 0;

   return retval;
}

void wired_test_recv_data(WiredLink * l, uint8_t * data, uint len, int * go) {
   while (!(*go)) std::this_thread::yield();
   l->recv(data,len);
}

int wired_server_send_link_recv_4() {

   int to_send_byte = 10000000;
   int threads = 4;

   WiredServer s;
   WiredLink l[threads];

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   for (int i = 0; i < threads; ++i)
      l[i].open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(10));

   std::vector<WiredServer::socktype> col;

   s.get_ready(col);

   for (int i = 0; i < 10; ++i) {
      col.clear();
      if (s.get_ready(col) == threads)
         break;
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
   }

   int retval = 1;

   if (col.size() != threads)
      retval = 0;

   uint8_t * tosend[threads];
   uint8_t * torecv[threads];
   std::thread th[threads];

   std::sort(col.begin(),col.end());

   for (int i = 0; i < threads; ++i) {
      tosend[i] = (uint8_t *)malloc(to_send_byte);
#ifdef _WIN32
      memset(tosend[i],0xff,to_send_byte);
#else
      memset(tosend[i],i,to_send_byte);
#endif
      s.send(col[i],tosend[i],to_send_byte);
   }

   for (int i = 0; i < threads; ++i) {
      torecv[i] = (uint8_t *)malloc(to_send_byte);
      memset(torecv[i],0,to_send_byte);
   }

   int go = 0;

   for (int i = 0; i < threads; ++i)
      th[i] = std::thread(&wired_test_recv_data,&l[i],torecv[i],to_send_byte,&go);

   std::this_thread::sleep_for(std::chrono::milliseconds(threads));

   go = 1;

   int retries = 20;
   col.clear();
   while (s.get_ready(col) != threads && retries--) { 
      col.clear(); std::this_thread::sleep_for(std::chrono::milliseconds(10));
   }

   for (int i = 0; i < threads; ++i) {
      if (th[i].joinable())
         th[i].join();
   }

   for (int i = 0; i < threads; ++i) {
      if (memcmp(tosend[i],torecv[i],to_send_byte) != 0)
         retval = 0;
   }

   for (int i = 0; i < threads; ++i) {
      free(tosend[i]);
      free(torecv[i]);
   }

   return retval;
}

int wired_server_send_link_recv_5() {
   WiredServer s;

   int retval = 1;

   if (s.send(20,(uint8_t *)&retval,sizeof(int)) != -1)
      retval = 0;

   return retval;
}

int wired_server_send_link_recv_6() {
   WiredServer s;
   WiredLink l;

   uint port = ((arc4random()%40000)+10000);
   s.start(port);
   l.open("localhost",port);

   std::this_thread::sleep_for(std::chrono::milliseconds(3));

   int retval = 1;

   if (s.send(20,(uint8_t *)&retval,sizeof(int)) != -1)
      retval = 0;

   return retval;
}

}

}
