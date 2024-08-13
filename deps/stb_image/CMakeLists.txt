cmake_minimum_required(VERSION 3.1)
project(stb_image)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "include/*.h")

add_library(stb_image STATIC ${SOURCE_FILES})
target_include_directories(stb_image PUBLIC "src")



