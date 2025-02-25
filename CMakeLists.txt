cmake_minimum_required(VERSION 3.29)
project(PixelSorting)

set(CMAKE_CXX_STANDARD 20)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}", "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_executable(PixelSorting main.cpp
        include/stb_image.cpp
        include/stb_image_write.cpp
        Effect.cpp
        Effect.h
        Palette.cpp
        Palette.h
        Pixelator.cpp
        Pixelator.h
        PixelSorter.cpp
        PixelSorter.h)
