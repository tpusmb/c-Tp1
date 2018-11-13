cmake_minimum_required(VERSION 3.12)
project(Tp1c__M1)

set(CMAKE_CXX_STANDARD 14)

# double-brightness.cpp
# filtrage-median.cpp
# egalise.cpp
# simple_convolution.cpp
add_executable(Tp1c__M1  GrayLevelImage2D.cpp GrayLevelImage2D.h Histogramme.h Histogramme.cpp image_clear.cpp)