cmake_minimum_required(VERSION 3.15)
project(Custom2DPhysicalEngine CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL3 REQUIRED)

# Add all engine source files to the executable
add_executable(Custom2DPhysicalEngine 
    src/main.cpp
    src/Physics.cpp 
)

# Specify the src folder as the include directory for header files (.h)
target_include_directories(Custom2DPhysicalEngine PRIVATE
    src
    ${CMAKE_SOURCE_DIR}/third_party/imgui
    ${CMAKE_SOURCE_DIR}/third_party/imgui/backends
)

# ImGui sources
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/third_party/imgui)

target_sources(Custom2DPhysicalEngine PRIVATE
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

target_link_libraries(Custom2DPhysicalEngine PRIVATE SDL3::SDL3)