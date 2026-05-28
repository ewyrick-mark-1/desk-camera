cmake_minimum_required(VERSION 3.3)

project(desk-camera)

find_package(OpenCV REQUIRED)

add_executable(cam ./src/main.cc)

target_include_directories(cam PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(cam PRIVATE ${OpenCV_LIBS})


