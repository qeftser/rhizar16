
add_library(selection_test "")

target_sources(selection_test 

   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/selection_test.cpp
   ${CMAKE_CURRENT_LIST_DIR}/selection_test_2.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/selection_test.h

)

target_link_libraries(selection_test base chromosome selection population)

target_include_directories(selection_test
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
