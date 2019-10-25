cmake_minimum_required(VERSION 3.10)

project(tbstudio)

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(${CMAKE_PROJECT_NAME} GUI/main.cpp)
