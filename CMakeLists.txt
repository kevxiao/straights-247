cmake_minimum_required(VERSION 3.2)
project(straights_247)

INCLUDE(FindPkgConfig)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB SOURCE_FILES
    "*.h"
    "*.cpp"
    "Models/*.cpp"
    "Models/*.h"
    "Controllers/*.cpp"
    "Controllers/*.h"
    "Views/*.cpp"
    "Views/*.h"
    "Lib/*.cpp"
    "Lib/*.h"
)

pkg_check_modules (GTKMM gtkmm-2.4)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(straights_247 ${SOURCE_FILES} Views/AllPlayersWidget.h Views/AllPlayersWidget.cpp Lib/Constants.h Views/PlayerWidget.h Views/PlayerWidget.cpp)

target_link_libraries(straights_247 ${GTKMM_LIBRARIES})