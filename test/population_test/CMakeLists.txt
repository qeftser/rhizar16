
add_library(population_test "")

target_sources(population_test 

   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/population_test.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/population_test.h

)

target_link_libraries(population_test base chromosome selection population selection_test)

target_include_directories(population_test
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
