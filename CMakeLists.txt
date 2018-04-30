cmake_minimum_required(VERSION 3.7.2)

project(lupulus)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++14")

if (${DEBUG} AND ${DEBUG} EQUAL 1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

file(GLOB SOURCES src/*.cc)
include_directories(include)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/)
file(GLOB HEADERS include/lupulus/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

# Test
# enable_testing()
# add_subdirectory(test)
