
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

add_library(file_test "")

target_sources(file_test
   
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/file_opts_test.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/file_opts_test.h

)

target_link_libraries(file_test file)

target_include_directories(file_test
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)

file(COPY test_files DESTINATION ${CMAKE_BINARY_DIR})

