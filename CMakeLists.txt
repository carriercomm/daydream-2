cmake_minimum_required(VERSION 3.0)
project(daydream)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/deps/include")

if(MINGW)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/deps/lib/mingw/x64")
elseif(MSVC)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/deps/lib/msvc12/x64")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fpermissive")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

#set(GLEW_INCLUDE_DIR ${daydream_SOURCE_DIR}/libs/glew-1.11.0/include)
#set(GLEW_LIBRARY ${daydream_SOURCE_DIR}/libs/glew-1.11.0/lib/Release/glew32.lib)

#set(GLFW_INCLUDE_DIR ${daydream_SOURCE_DIR}/libs/glfw-3.0.4/include)
#set(GLFW_LIBRARY ${daydream_SOURCE_DIR}/libs/glfw-3.0.4/lib/Release/glfw3dll.lib)

set(Boost_DEBUG ON)
set(Boost_USE_STATIC_LIBS on)
add_definitions(-DBOOST_ALL_NO_LIB)
#set(BOOST_INCLUDEDIR ${BOOST_ROOT}/boost)
#set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib32-msvc-12.0)
set(BOOST_LIBRARYDIR $ENV{BOOST_ROOT}/lib64-msvc-12.0)

#add_definitions(-DGLEW_MX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(src/dd)
add_subdirectory(src/game)
add_subdirectory(src/tests)
