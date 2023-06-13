cmake_minimum_required(VERSION 3.16.0)

set(CXX_STANDARD 20)

set(PROJECT_NAME Tensor)

project(${PROJECT_NAME} VERSION 0.1.0)

add_executable(${PROJECT_NAME}
    src/idx.cpp
    main.cpp
)