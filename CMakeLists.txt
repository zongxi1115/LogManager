cmake_minimum_required(VERSION 3.14)
project(my_logger)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# 使用 file(GLOB) 命令收集 src 目录下的所有源文件
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*/*.cpp" )
find_package(fmt CONFIG REQUIRED)
add_library(logger ${SOURCES})
target_link_libraries(logger PRIVATE fmt::fmt)

target_include_directories(logger PUBLIC include)

add_executable(demo examples/test.cpp )
# add_executable(demos examples/temp2.cpp )
add_executable(analyser examples/analyser.cpp )



target_link_libraries(demo logger)
target_link_libraries(analyser logger)

