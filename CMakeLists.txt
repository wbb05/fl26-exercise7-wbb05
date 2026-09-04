cmake_minimum_required(VERSION 3.10)
project(Exercise7 CXX)

# Executable for clientcode
add_executable(clientcode clientcode.cpp treap.cpp treap.h)

# Executable for unit test
add_executable(unit_test unit_test.cpp treap.cpp treap.h)

