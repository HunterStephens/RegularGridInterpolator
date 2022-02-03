cmake_minimum_required(VERSION 3.21)
project(RegularGridInterpolator)

set(CMAKE_CXX_STANDARD 17)

add_executable(RegularGridInterpolator main.cpp RegularGridInterpolator1D.h RegularGridInterpolator2D.h)
