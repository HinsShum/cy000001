# @file components/lwip/src/netif/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2020/12/16 22:00:40
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

file(GLOB CFILES "*.c")

# filter out the source files that u not want to compile
set(CFILES_OUT "")
filter_out(CFILES_OUT CFILES CFILES)

set(TARGET_C_FILES ${TARGET_C_FILES} ${CFILES} PARENT_SCOPE)
set(TARGET_INCLUDE_DIRS ${TARGET_INCLUDE_DIRS} PARENT_SCOPE)
