
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

find_package(SFML COMPONENTS window graphics system)

if (${SFML_FOUND})

   add_executable(traveling_salesman traveling_salesman_sfml.cpp)
   target_link_libraries(traveling_salesman PRIVATE chromosome population selection
                                            sfml-window sfml-graphics sfml-system)

else (${SFML_FOUND})

   add_executable(traveling_salesman traveling_salesman.cpp)
   target_link_libraries(traveling_salesman PRIVATE population chromosome selection)

endif (${SFML_FOUND})

