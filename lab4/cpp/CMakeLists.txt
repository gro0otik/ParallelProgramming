cmake_minimum_required(VERSION 3.20)
project(lab4 LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 14)

add_executable(lab4 main.cpp Multiplier.cu)

if(MSVC)
    target_compile_options(lab4 PRIVATE $<$<COMPILE_LANGUAGE:CXX>:/O2 /utf-8 /EHsc>)
endif()