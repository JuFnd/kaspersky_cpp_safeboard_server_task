cmake_minimum_required(VERSION 3.22.1)
project(server)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(server_binary ${SOURCE_FILES})
target_include_directories(server_binary PRIVATE 
        includes
)