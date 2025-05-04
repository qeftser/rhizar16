
add_executable(test test.cpp)

add_subdirectory(base_test)

target_link_libraries(test 
   PRIVATE
   base base_test
)
