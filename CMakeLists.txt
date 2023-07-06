cmake_minimum_required(VERSION 3.15)
project(Delphi)

set(VERSION 0.1.0)
set(FRIENDLY_VERSION "0.1.0")

if (DEFINED NT_NAME)
    MESSAGE(STATUS "Using provided name: ${NT_NAME}")
else (DEFINED NT_NAME)
    MESSAGE(STATUS "Using default name")
    set(NT_NAME "defaultName")
endif (DEFINED NT_NAME)

set(CMAKE_PREFIX_PATH ${CMAKE_MODULE_PATH} "build")

add_compile_definitions(VERSION="${FRIENDLY_VERSION}" NT_NAME="${NT_NAME}")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${CMAKE_MODULE_PATH} "src/main/include")

file(GLOB_RECURSE SOURCES CMAKE_CONFIGURE_DEPENDS "src/main/**.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})