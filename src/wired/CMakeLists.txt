
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

add_library(wired "")

set_target_properties(wired PROPERTIES LINKER_LANGUAGE CXX)

target_sources(wired

   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/wired_link.cpp
   ${CMAKE_CURRENT_LIST_DIR}/wired_server.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/wired_link.h
   ${CMAKE_CURRENT_LIST_DIR}/wired_server.h

)

target_include_directories(wired
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
