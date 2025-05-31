

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

add_library(file "")

set_target_properties(file PROPERTIES LINKER_LANGUAGE CXX)

target_sources(file

   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/file_opts.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/file_opts.h

)

target_include_directories(file
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
