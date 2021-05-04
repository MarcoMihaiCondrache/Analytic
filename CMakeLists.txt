cmake_minimum_required(VERSION 3.19)
project(Analytic C)

set(CMAKE_C_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(analytic)
include_directories(log)
include_directories(ui)

add_executable(Analytic
        analytic/src/analytic.c
        analytic/src/functions.c
        analytic/src/geometry.c
        analytic/src/plane.c
        analytic/src/scale.c
        analytic/analytic.h
        analytic/functions.h
        analytic/geometry.h
        analytic/global.h
        analytic/plane.h
        analytic/scale.h
        log/src/log.c
        log/log.h
        ui/src/input.c
        ui/src/output.c
        ui/global.h
        ui/input.h
        ui/output.h
        draw.c)

target_link_libraries(${PROJECT_NAME} SDL2::Main)