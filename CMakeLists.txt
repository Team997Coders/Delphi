cmake_minimum_required(VERSION 3.15)
project(Delphi)

set(VERSION 0.1.0)
set(FRIENDLY_VERSION "0.1.0")

if (DEFINED CONFIG_NAME)
    MESSAGE(STATUS "Using provided name: ${CONFIG_NAME}")
else (DEFINED CONFIG_NAME)
    MESSAGE(STATUS "Using default name")
    set(CONFIG_NAME "defaultName")
endif (DEFINED CONFIG_NAME)

if (DEFINED CONFIG_TEAMNUM)
    MESSAGE(STATUS "Using provided team number: ${CONFIG_TEAMNUM}")
else (DEFINED CONFIG_TEAMNUM)
    MESSAGE(STATUS "Using default team number")
    set(CONFIG_TEAMNUM "997")
endif (DEFINED CONFIG_TEAMNUM)

set(CMAKE_PREFIX_PATH ${CMAKE_MODULE_PATH} "build")

add_compile_definitions(VERSION="${FRIENDLY_VERSION}" CONFIG_NAME="${CONFIG_NAME}" CONFIG_TEAMNUM="${CONFIG_TEAMNUM}")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(wpinet REQUIRED)
find_package(cscore REQUIRED)
find_package(ntcore REQUIRED)

include_directories(${CMAKE_MODULE_PATH} "src/main/include")

file(GLOB_RECURSE SOURCES CMAKE_CONFIGURE_DEPENDS "src/main/**.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} wpinet cscore ntcore)