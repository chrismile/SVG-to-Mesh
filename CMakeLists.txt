cmake_minimum_required (VERSION 2.6)
project (svgtomesh)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
#MESSAGE(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

file(GLOB_RECURSE SOURCES src/*.cpp src/*.c)
add_executable(svgtomesh ${SOURCES})
include_directories(src)

#make VERBOSE=1

find_package(TinyXML2 REQUIRED)
find_package(PNG REQUIRED)
find_package(Boost COMPONENTS system filesystem regex REQUIRED)
target_link_libraries(svgtomesh png)
target_link_libraries(svgtomesh boost_system)
target_link_libraries(svgtomesh boost_filesystem)
target_link_libraries(svgtomesh boost_regex)
target_link_libraries(svgtomesh tinyxml2)

# For make install.
install (TARGETS svgtomesh DESTINATION bin)
