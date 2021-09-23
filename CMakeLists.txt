cmake_minimum_required (VERSION 2.6)
project (brogue)
include_directories(include)
file(GLOB SOURCES "src/*/*.c")

add_executable(brogue ${SOURCES})

target_link_libraries(brogue m)

add_definitions(-DBROGUE_CURSES)
find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )
target_link_libraries(brogue ${CURSES_LIBRARIES} )


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
