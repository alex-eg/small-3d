project(small-3d)
cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_SOURCE_DIR ./)
set(INCLUDE_DIR ./include)
set(SRC_DIR ./src)
set(EXECUTABLE_OUTPUT_PATH ./bin)
set(EXECUTABLE_NAME whatever)

set(SRCS
  ${SRC_DIR}/application.cpp
  ${SRC_DIR}/camera.cpp
  ${SRC_DIR}/event.cpp
  ${SRC_DIR}/shader.cpp
  ${SRC_DIR}/mesh.cpp)

include_directories(${INCLUDE_DIR})
  
add_executable(${EXECUTABLE_NAME} ${SRCS})

set(CMAKE_CXX_COMPILER clang)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ./)

set(CMAKE_CXX_FLAGS -std=c++11)
set(CMAKE_CXX_FLAGS_DEBUG -g)
set(CMAKE_CXX_FLAGS_RELEASE -O2)

find_package(SDL)
if (SDL_FOUND) 
  message("Found SDL...")
  include_directories(${SDL_INCLUDE_DIRS})
  target_link_libraries(${EXECUTABLE_NAME} ${SDL_LIBRARY})
endif(SDL_FOUND)

find_package(OpenGL)
if (OPENGL_FOUND)
  message("Found OpenGL...")
  include_directories(${OPENGL_INCLUDE_DIRS})
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARIES})
endif (OPENGL_FOUND)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  message("Found GLEW...")
  include_directories(${GLEW_INCLUDE_PATH})
  target_link_libraries(${EXECUTABLE_NAME} ${GLEW_LIBRARY})
endif (GLEW_FOUND)

if (UNIX) 
  target_link_libraries(${EXECUTABLE_NAME} -lstdc++)
endif (UNIX)
