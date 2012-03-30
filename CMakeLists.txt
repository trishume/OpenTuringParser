#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8)
#Name your project here
project(TuringParser)

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules )

#set(CMAKE_BINARY_DIR ${PROJECT_BINARY_DIR}/bin)

set(INSTALL_DIR ${PROJECT_SOURCE_DIR}/dist)

set(MAIN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)