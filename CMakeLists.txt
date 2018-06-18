cmake_minimum_required(VERSION 3.9)
project(RawPcmToWav)

set(CMAKE_C_STANDARD 11)

add_executable(RawPcmToWav main.c RawPcmToWav.c RawPcmToWav.h)