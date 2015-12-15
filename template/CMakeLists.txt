cmake_minimum_required(VERSION 2.8)

project(bricabrac)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} third-party/glimac/include third-party/glm third-party/assimp)

set(ALL_LIBRARIES glimac ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} assimp)

message(${SDL2_LIBRARY})

add_subdirectory(third-party)

file(GLOB projet_DIRECTORIES "projet*")

foreach(projet ${projet_DIRECTORIES})
    add_subdirectory(${projet})
endforeach()
