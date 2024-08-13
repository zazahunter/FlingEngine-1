cmake_minimum_required(VERSION 3.7)

project(imgui_entt_entity_editor)

file(GLOB IMGUI_ENTT_EDITOR_SRC "*.hpp")

add_library(${PROJECT_NAME} INTERFACE ${IMGUI_ENTT_EDITOR_SRC})

target_include_directories(${PROJECT_NAME} INTERFACE src)