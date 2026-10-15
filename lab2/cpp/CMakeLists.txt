cmake_minimum_required(VERSION 3.28)
project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
find_package(OpenMP REQUIRED)

if(MSVC)
    add_compile_options(/O2 /EHsc /utf-8 /std:c++latest)
endif()
add_executable(lab2)
target_compile_features(lab2 PUBLIC cxx_std_23)
target_link_libraries(lab2 PUBLIC OpenMP::OpenMP_CXX)

target_sources(lab2
    PRIVATE
        main.cpp
    PUBLIC
    FILE_SET CXX_MODULES FILES
        Multiplier.cppm
        IOMatrix.cppm
        RMatrix.cppm
) 