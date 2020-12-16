# @file components/lwip/src/core/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2020/12/16 21:50:32
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

file(GLOB CFILES "*.c")
file(GLOB IPV4_CFILES "ipv4/*.c")

# filter out the source files that u not want to compile
set(CFILES_OUT "")
filter_out(CFILES_OUT CFILES CFILES)

set(TARGET_C_FILES ${TARGET_C_FILES} ${CFILES} ${IPV4_CFILES} PARENT_SCOPE)
set(TARGET_INCLUDE_DIRS ${TARGET_INCLUDE_DIRS} PARENT_SCOPE)