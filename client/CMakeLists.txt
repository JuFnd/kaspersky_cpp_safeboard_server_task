cmake_minimum_required(VERSION 3.22.1)
project(client)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(client_binary ${SOURCE_FILES})
target_include_directories(client_binary PRIVATE 
        includes
)