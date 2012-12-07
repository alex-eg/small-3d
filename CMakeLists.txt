project(small-3d)
cmake_minimum_required(VERSION 2.8.0)

message(STATUS "System: " ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})

set(SRC_DIR ./)

set(SRCS
  ${SRC_DIR}/application.cpp
  ${SRC_DIR}/camera.cpp
  ${SRC_DIR}/event.cpp
  ${SRC_DIR}/shader.cpp
  ${SRC_DIR}/wavefrontLoader.cpp)
  
  
add_executable(app ${SRCS})

set(CMAKE_CXX_COMPILER clang)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ./)

set(LIBS -lstdc++)

set(CMAKE_CXX_FLAGS -std=c++11)

set(CMAKE_CXX_FLAGS_DEBUG -g)
set(CMAKE_CXX_FLAGS_RELEASE -O2)

find_package(GLEW REQUIRED)


find_package(SDL)
if (SDL_FOUND) 
  message("Found SDL...")
  include_directories(${SDL_INCLUDE_DIRS})
  target_link_libraries(app ${SDL_LIBRARY})
endif(SDL_FOUND)

find_package(OpenGL)
if (OPENGL_FOUND)
  message("Found OpenGL...")
  include_directories(${OPENGL_INCLUDE_DIRS})
  target_link_libraries(app ${OPENGL_gl_LIBRARIES})
endif (OPENGL_FOUND)

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  message("Found GLEW...")
  include_directories(${GLEW_INCLUDE_PATH})
  target_link_libraries(app ${GLEW_LIBRARY})
endif (GLEW_FOUND)

if (UNIX) 
  target_link_libraries(app -lstdc++)
endif (UNIX)