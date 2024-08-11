cmake_minimum_required(VERSION 3.28)
project(MyWeb)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyWeb main.cpp)

# Link with the WinSock2 library
target_link_libraries(MyWeb ws2_32)
