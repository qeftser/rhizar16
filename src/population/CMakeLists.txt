
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

add_library(population "")

set_target_properties(population PROPERTIES LINKER_LANGUAGE CXX)

target_sources(population

   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/thread_pond.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/population.h
   ${CMAKE_CURRENT_LIST_DIR}/thread_pond.h
   ${CMAKE_CURRENT_LIST_DIR}/concurrent_queue.h

)

target_include_directories(population
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
