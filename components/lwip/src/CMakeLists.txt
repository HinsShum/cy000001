# @file components/lwip/src/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2020/12/16 21:43:29
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

set(CMAKELISTS_DIRS)
set(SRC_INC_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/include/ipv4")

# get sub directory
file(GLOB_RECURSE CMAKELISTS "CMakeLists.txt")
dirname(CMAKELISTS CMAKELISTS_DIRS)
filter_out(CMAKE_CURRENT_SOURCE_DIR CMAKELISTS_DIRS CMAKELISTS_DIRS)
foreach(SUB_DIRECTORY ${CMAKELISTS_DIRS})
    add_subdirectory(${SUB_DIRECTORY})
endforeach(SUB_DIRECTORY)

set(TARGET_C_FILES ${TARGET_C_FILES} PARENT_SCOPE)
set(TARGET_INCLUDE_DIRS ${TARGET_INCLUDE_DIRS} ${SRC_INC_DIRS} PARENT_SCOPE)