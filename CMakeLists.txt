cmake_minimum_required(VERSION 3.3)
project(Viola_Jones_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    bin/Debug/vj_cpp.exe
    .gitattributes
    .gitignore
    class.txt
    Face.pgm
    haar.cpp
    haar.h
    image.c
    image.h
    info.txt
    LICENSE
    main.cpp
    Makefile
    Output.pgm
    rectangles.cpp
    stdio-wrapper.c
    stdio-wrapper.h
    vj_cpp.cbp
    vj_cpp.cscope_file_list
    vj_cpp.depend
    vj_cpp.layout)

add_executable(Viola_Jones_cpp ${SOURCE_FILES})