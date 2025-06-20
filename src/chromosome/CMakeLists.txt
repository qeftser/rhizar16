
add_library(chromosome "")

set_target_properties(chromosome PROPERTIES LINKER_LANGUAGE CXX)

target_sources(chromosome

   PRIVATE

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/bit_string.h
   ${CMAKE_CURRENT_LIST_DIR}/num_string.h
   ${CMAKE_CURRENT_LIST_DIR}/chromosome.h

)

target_include_directories(chromosome
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
