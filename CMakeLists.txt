cmake_minimum_required(VERSION 3.14)
project(project-1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(project-1)

target_sources(project-1
    PRIVATE ${SOURCES}
)
