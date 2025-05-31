
#include "file_opts_test.h"
#include <string>

namespace Rhizar16 {

int TestFileOpts::initialization_0() {

   FileOptions fo;

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string(""))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 0)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 0)
      retval = 0;

   return retval;
}

int TestFileOpts::load_0() {

   FileOptions fo;

   fo.load("test_files/empty.ini",FileOptions::Format::INI);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 0)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 0)
      retval = 0;

   return retval;
}

int TestFileOpts::load_1() {

   FileOptions fo;

   fo.load("test_files/empty.json",FileOptions::Format::JSON);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 0)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 0)
      retval = 0;

   return retval;
}

int TestFileOpts::load_2() {

   FileOptions fo;

   fo.load("test_files/empty.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 0)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 0)
      retval = 0;

   return retval;
}

int TestFileOpts::load_3() {

   FileOptions fo;

   fo.load("test_files/empty.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 0)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 0)
      retval = 0;

   return retval;
}

int TestFileOpts::load_4() {

   FileOptions fo;

   fo.load("test_files/empty.json",FileOptions::Format::INI);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 0)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 0)
      retval = 0;

   return retval;
}

int TestFileOpts::load_5() {

   FileOptions fo;

   fo.load("test_files/empty.ini",FileOptions::Format::JSON);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 0)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 0)
      retval = 0;

   return retval;
}

int TestFileOpts::load_6() {

   FileOptions fo;
   
   fo.load("test_files/good.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 0)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 0)
      retval = 0;

   return retval;
}

int TestFileOpts::load_7() {

   FileOptions fo;
   
   fo.load("test_files/good.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 0)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 0)
      retval = 0;

   return retval;
}

int TestFileOpts::load_8() {

   FileOptions fo;
   
   fo.load("test_files/nonexistant");

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_FILE)
      retval = 0;

   return retval;
}

int TestFileOpts::load_9() {

   FileOptions fo;
   
   fo.load("test_files/bad0.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 2)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 4)
      retval = 0;

   return retval;
}

int TestFileOpts::load_a() {
   FileOptions fo;
   
   fo.load("test_files/bad1.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 2)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 6)
      retval = 0;

   return retval;
}

int TestFileOpts::load_b() {
   FileOptions fo;
   
   fo.load("test_files/bad2.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 5)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 5)
      retval = 0;

   return retval;
}

int TestFileOpts::load_c() {
   FileOptions fo;
   
   fo.load("test_files/bad3.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 8)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 1)
      retval = 0;

   return retval;
}

int TestFileOpts::load_d() {
   FileOptions fo;
   
   fo.load("test_files/bad5.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 5)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 2)
      retval = 0;

   return retval;
}

int TestFileOpts::load_e() {
   FileOptions fo;
   
   fo.load("test_files/bad6.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 4)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 3)
      retval = 0;

   return retval;
}

int TestFileOpts::load_f() {
   FileOptions fo;
   
   fo.load("test_files/bad7.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 8)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 1)
      retval = 0;

   return retval;
}

int TestFileOpts::load_g() {
   FileOptions fo;
   
   fo.load("test_files/bad0.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 5)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 1)
      retval = 0;

   return retval;
}

int TestFileOpts::load_h() {
   FileOptions fo;
   
   fo.load("test_files/bad1.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 2)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 3)
      retval = 0;

   return retval;
}

int TestFileOpts::load_i() {
   FileOptions fo;
   
   fo.load("test_files/bad2.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 3)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 14)
      retval = 0;

   return retval;
}

int TestFileOpts::load_j() {
   FileOptions fo;
   
   fo.load("test_files/bad3.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 4)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 4)
      retval = 0;

   return retval;
}

int TestFileOpts::load_k() {
   FileOptions fo;
   
   fo.load("test_files/bad4.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 5)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 4)
      retval = 0;

   return retval;
}

int TestFileOpts::load_l() {
   FileOptions fo;
   
   fo.load("test_files/bad5.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 6)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 7)
      retval = 0;

   return retval;
}

int TestFileOpts::load_m() {
   FileOptions fo;
   
   fo.load("test_files/bad6.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 6)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 13)
      retval = 0;

   return retval;
}

int TestFileOpts::load_n() {
   FileOptions fo;
   
   fo.load("test_files/bad7.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 7)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 4)
      retval = 0;

   return retval;
}

int TestFileOpts::load_o() {
   FileOptions fo;
   
   fo.load("test_files/bad8.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 10)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 1)
      retval = 0;

   return retval;
}

int TestFileOpts::load_p() {
   FileOptions fo;
   
   fo.load("test_files/bad9.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 8)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 1)
      retval = 0;

   return retval;
}

int TestFileOpts::load_q() {
   FileOptions fo;
   
   fo.load("test_files/bad10.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::BAD_FORMAT)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   if (std::get<0>(fo.err_pos()) != 7)
      retval = 0;

   if (std::get<1>(fo.err_pos()) != 4)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_int_0() {
   FileOptions fo("test_files/good.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.getopt_int("Section0","Key00") != 324)
      retval = 0;

   if (fo.getopt_int("Section0","Key03") != 4324)
      retval = 0;

   if (fo.getopt_int("Section2","Key20") != 5834)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_int_1() {
   FileOptions fo("test_files/good.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.getopt_int("Section1","Key10") != 425)
      retval = 0;

   if (fo.getopt_int("Section2","Key20") != 545)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_int_2() {
   FileOptions fo;

   fo.getopt_int("section","key");

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_int_3() {
   FileOptions fo("test_files/good.ini");

   fo.getopt_int("Section0","Key11");

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_int_4() {
   FileOptions fo("test_files/good.json");

   fo.getopt_int("Section0","Key11");

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_int_5() {
   FileOptions fo("test_files/good.json");

   fo.getopt_int("Section0","Key03");

   int retval = 1;

   if (fo.status() != FileOptions::Status::WRONG_DATATYPE)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_int_6() {
   FileOptions fo("test_files/good.ini");

   fo.getopt_int("Section0","Key02");

   int retval = 1;

   if (fo.status() != FileOptions::Status::WRONG_DATATYPE)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_flt_0() {

   FileOptions fo("test_files/good.ini");

   int retval = 1;

   if (fo.getopt_flt("Section1","Key10") != 2343.123)
      retval = 0;

   if (fo.getopt_flt("Section1","Key13") != 798.424)
      retval = 0;

   if (fo.getopt_flt("Section3","Key32") != 76953.234)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_flt_1() {

   FileOptions fo("test_files/good.json");

   int retval = 1;

   if (fo.getopt_flt("Section1","Key12") != 35905.284392)
      retval = 0;

   if (fo.getopt_flt("Section2","Key12") != 0.284392)
      retval = 0;

   if (fo.getopt_flt("Section2","Key13") != 5093.242)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_flt_2() {

   FileOptions fo("test_files/good.json");

   fo.getopt_flt("SectionN","key");

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_flt_3() {

   FileOptions fo("test_files/good.ini");

   fo.getopt_flt("SectionN","key");

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_flt_4() {

   FileOptions fo("test_files/good.ini");

   fo.getopt_flt("Section1","KeyN");

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_flt_5() {

   FileOptions fo("test_files/good.json");

   fo.getopt_flt("Section1","KeyN");

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_flt_6() {

   FileOptions fo("test_files/good.json");

   fo.getopt_flt("Section1","Key11");

   int retval = 1;

   if (fo.status() != FileOptions::Status::WRONG_DATATYPE)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_str_0() {

   FileOptions fo("test_files/good.json");

   int retval = 1;

   if (fo.getopt_str("Section0","Key03") != std::string("Val3"))
      retval = 0;

   if (fo.getopt_str("Section1","Key10") != std::string("425"))
      retval = 0;

   if (fo.getopt_str("Section2","Key21") != std::string("Val1"))
      retval = 0;

   if (fo.getopt_str("Section2","Key13") != std::string("5093.242"))
      retval = 0;

   if (fo.getopt_str("Section3","Key30") != std::string("  Val0  "))
      retval = 0;

   if (fo.getopt_str("Section3","Key33") != std::string("  Val3"))
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_str_1() {

   FileOptions fo("test_files/good.ini");

   int retval = 1;

   if (fo.getopt_str("Section0","Key02") != std::string("Val2"))
      retval = 0;

   if (fo.getopt_str("Section0","Key03") != std::string("4324"))
      retval = 0;

   if (fo.getopt_str("Section1","Key13") != std::string("798.424"))
      retval = 0;

   if (fo.getopt_str("Section2","Key21") != std::string("  Val1 is a long value  "))
      retval = 0;

   if (fo.getopt_str("Section2","Key22") != std::string("Val2 is a sentence that"))
      retval = 0;

   if (fo.getopt_str("Section3","Key30") != std::string("Val0"))
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_str_2() {

   FileOptions fo("test_files/good.ini");

   int retval = 1;

   fo.getopt_str("SectionN","key");

   if (fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_str_3() {

   FileOptions fo("test_files/good.json");

   int retval = 1;

   fo.getopt_str("SectionN","key");

   if (fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_str_4() {

   FileOptions fo("test_files/good.json");

   int retval = 1;

   fo.getopt_str("Section1","KeyN");

   if (fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   return retval;
}

int TestFileOpts::getopt_str_5() {

   FileOptions fo("test_files/good.ini");

   int retval = 1;

   fo.getopt_str("Section1","KeyN");

   if (fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   return retval;
}

int TestFileOpts::has_section_0() {

   FileOptions fo("test_files/good.ini");

   int retval = 1;

   if (!fo.has_section("Section0") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_section("Section1") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_section("Section2") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_section("Section3") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   return retval;
}

int TestFileOpts::has_section_1() {

   FileOptions fo("test_files/good.json");

   int retval = 1;

   if (!fo.has_section("Section0") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_section("Section1") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_section("Section2") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_section("Section3") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   return retval;
}

int TestFileOpts::has_section_2() {

   FileOptions fo("test_files/good.ini");

   int retval = 1;

   if (fo.has_section("Section4") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_section("Section5") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_section("Section6") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_section("Section7") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::has_section_3() {

   FileOptions fo("test_files/good.ini");

   int retval = 1;

   if (fo.has_section("Section4") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_section("Section5") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_section("Section6") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_section("Section7") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::has_key_0() {

   FileOptions fo("test_files/good.ini");

   int retval = 1;

   if (!fo.has_key("Section0","Key03") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_key("Section1","Key12") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_key("Section2","Key21") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_key("Section3","Key30") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   return retval;
}

int TestFileOpts::has_key_1() {

   FileOptions fo("test_files/good.json");

   int retval = 1;

   if (!fo.has_key("Section0","Key03") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_key("Section1","Key12") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_key("Section2","Key21") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (!fo.has_key("Section3","Key30") || fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   return retval;
}

int TestFileOpts::has_key_2() {

   FileOptions fo("test_files/good.json");

   int retval = 1;

   if (fo.has_key("Section4","Key03") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_key("Section5","Key12") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_key("Section6","Key21") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_key("Section7","Key30") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::has_key_3() {

   FileOptions fo("test_files/good.ini");

   int retval = 1;

   if (fo.has_key("Section4","Key03") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_key("Section5","Key12") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_key("Section6","Key21") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   if (fo.has_key("Section7","Key30") || fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::has_key_4() {

   FileOptions fo("test_files/good.ini");

   int retval = 1;

   if (fo.has_key("Section0","Key33") || fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   if (fo.has_key("Section1","Key22") || fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   if (fo.has_key("Section2","Key11") || fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   if (fo.has_key("Section3","Key00") || fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   return retval;
}

int TestFileOpts::has_key_5() {

   FileOptions fo("test_files/good.json");

   int retval = 1;

   if (fo.has_key("Section0","Key33") || fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   if (fo.has_key("Section1","Key22") || fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   if (fo.has_key("Section2","Key11") || fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   if (fo.has_key("Section3","Key00") || fo.status() != FileOptions::Status::NO_KEY)
      retval = 0;

   return retval;
}

int TestFileOpts::save_0() {

   FileOptions fo("test_files/good.ini");

   fo.save("test_files/out");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   remove("test_files/out");
   return retval;
}

int TestFileOpts::save_1() {

   FileOptions fo;

   fo.save("test_files/out");

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_FILE)
      retval = 0;

   remove("test_files/out");
   return retval;
}

int TestFileOpts::save_2() {

   FileOptions fo("test_files/good.ini");

   fo.save("test_files/out.ini");

   fo.load("test_files/out.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   remove("test_files/out.ini");
   return retval;
}

int TestFileOpts::save_3() {

   FileOptions fo("test_files/good.ini");

   fo.save("test_files/out.ini");

   fo.load("test_files/out.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   remove("test_files/out.ini");
   return retval;
}

int TestFileOpts::save_4() {

   FileOptions fo("test_files/good.ini");

   fo.save("test_files/out.ini",FileOptions::Format::JSON);

   fo.load("test_files/out.ini",FileOptions::Format::JSON);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   remove("test_files/out.ini");
   return retval;
}

int TestFileOpts::save_5() {

   FileOptions fo("test_files/good.ini");

   fo.save("test_files/out.json");

   fo.load("test_files/out.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   remove("test_files/out.json");
   return retval;
}

int TestFileOpts::save_6() {

   FileOptions fo("test_files/good.ini");

   fo.save("test_files/out.json",FileOptions::Format::INI);

   fo.load("test_files/out.json",FileOptions::Format::INI);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   remove("test_files/out.json");
   return retval;
}

int TestFileOpts::save_7() {

   FileOptions fo("test_files/good.json");

   fo.save("test_files/out.ini");

   fo.load("test_files/out.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   remove("test_files/out.ini");
   return retval;
}

int TestFileOpts::save_8() {

   FileOptions fo("test_files/good.json");

   fo.save("test_files/out.ini");

   fo.load("test_files/out.ini");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   remove("test_files/out.ini");
   return retval;
}

int TestFileOpts::save_9() {

   FileOptions fo("test_files/good.json");

   fo.save("test_files/out.ini",FileOptions::Format::JSON);

   fo.load("test_files/out.ini",FileOptions::Format::JSON);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   remove("test_files/out.ini");
   return retval;
}

int TestFileOpts::save_a() {

   FileOptions fo("test_files/good.json");

   fo.save("test_files/out.json");

   fo.load("test_files/out.json");

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("JSON"))
      retval = 0;

   remove("test_files/out.json");
   return retval;
}

int TestFileOpts::save_b() {

   FileOptions fo("test_files/good.json");

   fo.save("test_files/out.json",FileOptions::Format::INI);

   fo.load("test_files/out.json",FileOptions::Format::INI);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (fo.fformat() != std::string("INI"))
      retval = 0;

   remove("test_files/out.json");
   return retval;
}

int TestFileOpts::collect_sections_0() {

   FileOptions fo;

   std::vector<std::string> sections;

   fo.collect_sections(sections);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   return retval;
}

int TestFileOpts::collect_sections_1() {

   FileOptions fo("test_files/good.ini");

   std::vector<std::string> sections;

   fo.collect_sections(sections);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (sections[0] != std::string("Section0"))
      retval = 0;
   if (sections[1] != std::string("Section1"))
      retval = 0;
   if (sections[2] != std::string("Section2"))
      retval = 0;
   if (sections[3] != std::string("Section3"))
      retval = 0;

   return retval;
}

int TestFileOpts::collect_sections_2() {

   FileOptions fo("test_files/good.json");

   std::vector<std::string> sections;

   fo.collect_sections(sections);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (sections[0] != std::string("Section0"))
      retval = 0;
   if (sections[1] != std::string("Section1"))
      retval = 0;
   if (sections[2] != std::string("Section2"))
      retval = 0;
   if (sections[3] != std::string("Section3"))
      retval = 0;

   return retval;
}

int TestFileOpts::collect_keys_0() {
   FileOptions fo;

   std::vector<std::string> keys;

   fo.collect_keys("Section0",keys);

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::collect_keys_1() {
   FileOptions fo("test_files/good.ini");

   std::vector<std::string> keys;

   fo.collect_keys("SectionN",keys);

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::collect_keys_2() {
   FileOptions fo("test_files/good.json");

   std::vector<std::string> keys;

   fo.collect_keys("SectionN",keys);

   int retval = 1;

   if (fo.status() != FileOptions::Status::NO_SECTION)
      retval = 0;

   return retval;
}

int TestFileOpts::collect_keys_3() {
   FileOptions fo("test_files/good.json");

   std::vector<std::string> keys;

   fo.collect_keys("Section0",keys);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (keys[0] != std::string("Key00"))
      retval = 0;
   if (keys[1] != std::string("Key01"))
      retval = 0;
   if (keys[2] != std::string("Key02"))
      retval = 0;
   if (keys[3] != std::string("Key03"))
      retval = 0;

   return retval;
}

int TestFileOpts::collect_keys_4() {
   FileOptions fo("test_files/good.ini");

   std::vector<std::string> keys;

   fo.collect_keys("Section3",keys);

   int retval = 1;

   if (fo.status() != FileOptions::Status::SUCCESS)
      retval = 0;

   if (keys[0] != std::string("Key30"))
      retval = 0;
   if (keys[1] != std::string("Key31"))
      retval = 0;
   if (keys[2] != std::string("Key32"))
      retval = 0;
   if (keys[3] != std::string("Key33"))
      retval = 0;

   return retval;
}

}
