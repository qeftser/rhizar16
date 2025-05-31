
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

add_executable(test test.cpp)

add_subdirectory(base_test)
add_subdirectory(chromosome_test)
add_subdirectory(selection_test)
add_subdirectory(population_test)
add_subdirectory(file_test)

target_link_libraries(test 
   PRIVATE
   base base_test
   chromosome chromosome_test
   selection selection_test
   population population_test
   file file_test
)
