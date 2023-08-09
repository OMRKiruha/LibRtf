cmake_minimum_required(VERSION 3.20)
project(libRtf)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(c)
include_directories(cpp)

add_library(Rtf
        c/convert.c
        c/convert.h
        c/ext.c
        c/librtf.c
        c/librtf.h
        c/parser.c
        c/parser.h
        c/processor.h
        c/rtfproc.c
        c/textproc.h
        cpp/html.cpp
        cpp/librtfcpp.cpp
        cpp/librtfcpp.h
        cpp/text.cpp
        cpp/text.h
        RtfReader.cpp
        RtfReader.h)
