cmake_minimum_required(VERSION 3.10)

project(tbstudio)

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

set(MathGL2_DIR /root/mathgl-2.4.4-mingw.win32)
find_package(MathGL2 REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} GUI/main.cpp)
