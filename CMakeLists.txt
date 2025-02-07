cmake_minimum_required(VERSION 3.10)
project(Xoner)

set(CMAKE_CXX_STANDARD 17)

# Add dependencies
find_package(CURL REQUIRED)

add_executable(backend backend.cpp)
target_link_libraries(backend CURL::libcurl)
