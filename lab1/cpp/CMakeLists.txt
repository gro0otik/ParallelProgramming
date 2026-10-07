cmake_minimum_required(VERSION 3.28)
project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_executable(lab1)
target_compile_features(lab1 PUBLIC cxx_std_23)

target_sources(lab1
        PRIVATE
                main.cpp
        PUBLIC
        FILE_SET "modules" TYPE CXX_MODULES FILES
                Multiplier.cppm
                IOMatrix.cppm
                RMatrix.cppm
)               