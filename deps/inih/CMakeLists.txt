cmake_minimum_required(VERSION 3.10)

project(Inih)

file(GLOB INIH_SOURCES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} STATIC ${INIH_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src)