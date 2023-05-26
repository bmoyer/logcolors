cmake_minimum_required(VERSION 3.23)
project(logcolors)

set(CMAKE_CXX_STANDARD 17)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(./include)

add_executable(logcolors src/main.cpp src/SharedDataTypes.cpp src/ConfigReader.cpp src/Renderer.cpp)
target_link_libraries(logcolors ${OpenCV_LIBS})