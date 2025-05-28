
add_library(base "")

target_sources(base

   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/uniform_rand.cpp
   ${CMAKE_CURRENT_LIST_DIR}/utils.cpp

   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}/uniform_rand.h
   ${CMAKE_CURRENT_LIST_DIR}/utils.h

)

target_include_directories(base
   PUBLIC
   ${CMAKE_CURRENT_LIST_DIR}
)
