
add_library(selection "")

set_target_properties(selection PROPERTIES LINKER_LANGUAGE CXX)

target_sources(selection

   PRIVATE

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/selection.h
   ${CMAKE_CURRENT_LIST_DIR}/roulette_selection.h
   ${CMAKE_CURRENT_LIST_DIR}/random_selection.h
   ${CMAKE_CURRENT_LIST_DIR}/rank_selection.h
   ${CMAKE_CURRENT_LIST_DIR}/tournament_selection.h
   ${CMAKE_CURRENT_LIST_DIR}/stochastic_selection.h

)

target_link_libraries(selection population)

target_include_directories(selection
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
