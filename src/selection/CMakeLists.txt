
add_library(selection "")

set_target_properties(selection PROPERTIES LINKER_LANGUAGE CXX)

target_sources(selection

   PRIVATE

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/selection.h

)

target_include_directories(selection
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
