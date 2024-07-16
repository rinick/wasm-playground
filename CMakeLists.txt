cmake_minimum_required(VERSION 3.5)

project(wasm-playground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(wasm-playground main.cpp
    hero.h hero.cpp
    tile.h tile.cpp
    force.h force.cpp
    hero.cpp
    output-image.h output-image.cpp)

target_link_options(wasm-playground PRIVATE
        -sEXPORTED_FUNCTIONS=['_main','_gettiles','_updateTile','_run'])

include(GNUInstallDirs)
install(TARGETS wasm-playground
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
