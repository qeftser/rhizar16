
add_library(population_test "")

target_sources(population_test 

   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/population_test.cpp
   ${CMAKE_CURRENT_LIST_DIR}/concurrent_queue_test.cpp
   ${CMAKE_CURRENT_LIST_DIR}/thread_pond_test.cpp
   ${CMAKE_CURRENT_LIST_DIR}/population_options_test.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/population_test.h
   ${CMAKE_CURRENT_LIST_DIR}/concurrent_queue_test.h
   ${CMAKE_CURRENT_LIST_DIR}/thread_pond_test.h
   ${CMAKE_CURRENT_LIST_DIR}/population_options_test.h

)

target_link_libraries(population_test 
                      base chromosome selection 
                      population selection_test)

target_include_directories(population_test
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)

file(COPY poptions DESTINATION ${CMAKE_BINARY_DIR})
