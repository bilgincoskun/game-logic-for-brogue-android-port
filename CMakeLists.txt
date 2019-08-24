cmake_minimum_required (VERSION 2.6)
project (brogue)
include_directories(include)
file(GLOB SOURCES "src/*/*.c")

add_executable(brogue ${SOURCES})

target_link_libraries(brogue m)

option(WITH_TCOD "build with tcod UI" ON)
option(WITH_CURSES "build with curses UI" ON)

if (WITH_TCOD)
    add_definitions(-DBROGUE_TCOD)
    include(FindPkgConfig)
    pkg_search_module(SDL2 REQUIRED sdl2)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(brogue  ${SDL2_LIBRARIES} tcod)
endif()

if (WITH_CURSES)
    add_definitions(-DBROGUE_CURSES)
    find_package( Curses REQUIRED )
    include_directories( ${CURSES_INCLUDE_DIRS} )
    target_link_libraries(brogue ${CURSES_LIBRARIES} )
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
