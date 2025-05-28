
add_library(base_test "")

target_sources(base_test
   
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/uniform_rand_test.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/uniform_rand_test.h

)

target_link_libraries(base_test base)

target_include_directories(base_test
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
