# 需求的最低cmake版本
cmake_minimum_required(VERSION 3.12)

# 工程名称
project(OpenGL_Lecture)

# 工程支持的最低c++版本
set(CAMKE_CXX_STANDARD 17)

# 向项目中加入全局预编译宏
add_definitions(-DDEBUG)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include)

link_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib)

add_subdirectory(wrapper)

# 工程exe
add_executable(openglStudy "main.cpp" "glad.c")

target_link_libraries(openglStudy glfw3.lib wrapper)