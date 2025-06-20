
add_library(chromosome_test "")

target_sources(chromosome_test
   
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/bit_string_test.cpp
   ${CMAKE_CURRENT_LIST_DIR}/num_string_test.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/bit_string_test.h
   ${CMAKE_CURRENT_LIST_DIR}/num_string_test.h

)

target_link_libraries(chromosome_test base chromosome)

target_include_directories(chromosome_test
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
