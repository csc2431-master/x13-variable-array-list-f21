cmake_minimum_required(VERSION 3.10)
project(VariableArrayList)

set(CMAKE_CXX_STANDARD 14)

add_executable(VariableArrayList main.cpp  FixedArrayList.h VariableArrayList.h ArrayList.h)