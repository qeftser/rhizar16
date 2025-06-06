
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

add_library(wired_test "")

target_sources(wired_test
   
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/wired_test.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/wired_test.h

)

target_link_libraries(wired_test wired)

target_include_directories(wired_test
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)

