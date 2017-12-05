cmake_minimum_required(VERSION 2.8)

project(Horsies)

set(CMAKE_CXX_STANDARD 14)

# set(CMAKE_CXX_FLAGS "--std=c++14 -g ${CMAKE_CXX_FLAGS}")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(include/)

set(SRC_FILES
	horsies.cpp
	src/hrhorsie.cpp
	src/hrmessage.cpp
	src/hrsdl2.cpp
	src/hrtexture.cpp
	)

add_executable(horsies ${SRC_FILES})

target_link_libraries(horsies ${SDL2_LIBRARIES} SDL2_image SDL2_mixer)