# Project definition
cmake_minimum_required(VERSION 3.1)
project(main)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(SOURCES "${SRC_DIR}/main.cpp" "${SRC_DIR}/shader.cpp" "${SRC_DIR}/shader.h"
            "${SRC_DIR}/util.cpp" "${SRC_DIR}/util.h" "${SRC_DIR}/text_handler.cpp" "${SRC_DIR}/text_handler.h"
            "${SRC_DIR}/camera.cpp" "${SRC_DIR}/camera.h" "${SRC_DIR}/window.cpp" "${SRC_DIR}/window.h"
            "${SRC_DIR}/maze.cpp" "${SRC_DIR}/maze.h" "${SRC_DIR}/sprite.cpp" "${SRC_DIR}/sprite.h"
            "${SRC_DIR}/player.cpp" "${SRC_DIR}/player.h" "${SRC_DIR}/movable_sprite.cpp" "${SRC_DIR}/movable_sprite.h"
            "${SRC_DIR}/game.cpp" "${SRC_DIR}/game.h" "${SRC_DIR}/button.cpp" "${SRC_DIR}/button.h"
            "${SRC_DIR}/character.cpp" "${SRC_DIR}/character.h" "${SRC_DIR}/imposter.cpp" "${SRC_DIR}/imposter.h"
            "${SRC_DIR}/coin.cpp" "${SRC_DIR}/coin.h" "${SRC_DIR}/bomb.cpp" "${SRC_DIR}/bomb.h")

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# glm
set(GLM_DIR "${LIB_DIR}/glm")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLM_DIR}/include")

# freetype
find_package(Freetype REQUIRED)
SET(CMAKE_EXE_LINKER_FLAGS "-v")
target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
