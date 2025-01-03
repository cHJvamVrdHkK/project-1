cmake_minimum_required(VERSION 3.29)
project(project-1 VERSION 1.0.0)

set(VCS_OUTPUT_DIRECTORY_BASE ${PROJECT_SOURCE_DIR}/artefacts/${CMAKE_BUILD_TYPE}-${CMAKE_HOST_SYSTEM_NAME})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${VCS_OUTPUT_DIRECTORY_BASE}/project-1/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${VCS_OUTPUT_DIRECTORY_BASE}/project-1/shared)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${VCS_OUTPUT_DIRECTORY_BASE}/project-1/bin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(project-1)

target_include_directories(project-1
        PRIVATE
            src/car_config.hpp
            src/car_model.hpp
            src/program.hpp
            src/components/car_color.hpp
            src/components/car_component.hpp
            src/components/car_engine.hpp
            src/components/car_wheels.hpp
)
target_sources(project-1
        PRIVATE
            src/car_config.cpp
            src/car_model.cpp
            src/main.cpp
            src/program.cpp
            src/components/car_color.cpp
            src/components/car_engine.cpp
            src/components/car_wheels.cpp
)
