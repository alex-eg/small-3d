project(small-3d)
cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_SOURCE_DIR ./)
set(INCLUDE_DIR ./include)
set(SRC_DIR ./src)
set(EXECUTABLE_OUTPUT_PATH ./)
set(EXECUTABLE_NAME whatever)

set(SRCS
  ${SRC_DIR}/application.cpp
  ${SRC_DIR}/camera.cpp
  ${SRC_DIR}/event.cpp
  ${SRC_DIR}/shader.cpp
  ${SRC_DIR}/mesh.cpp
  ${SRC_DIR}/propPosition.cpp
  ${SRC_DIR}/propGraphics.cpp
)

include_directories(${INCLUDE_DIR})

add_executable(${EXECUTABLE_NAME} ${SRCS})

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ./)

set(CMAKE_CXX_FLAGS -std=c++11)
set(CMAKE_CXX_FLAGS_DEBUG -ggdb)
set(CMAKE_CXX_FLAGS_RELEASE -O2)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_definitions(-DGLM_FORCE_RADIANS)

target_link_libraries(${EXECUTABLE_NAME} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL_LIBRARY})
