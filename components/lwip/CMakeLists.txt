# @file components/lwip/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2020/12/16 21:28:42
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

set(TARGET_LIB_NAME lwip)
set(TARGET_C_FILES)
set(TARGET_INCLUDE_DIRS)

# enter sub directory to execute CMakeLists.txt
add_subdirectory(src)

# compile target
add_library(${TARGET_LIB_NAME} STATIC ${TARGET_C_FILES})

# set head directory for compiling target
target_include_directories(${TARGET_LIB_NAME} PRIVATE ${G_SOURCE_INCLUDE_DIRS} ${TARGET_INCLUDE_DIRS})

# set global library for compiling main program
set(C_SOURCE_LIBS ${C_SOURCE_LIBS} ${TARGET_LIB_NAME} PARENT_SCOPE)

# set global head directory for compiling main program
set(G_SOURCE_INCLUDE_DIRS ${G_SOURCE_INCLUDE_DIRS} ${TARGET_INCLUDE_DIRS} PARENT_SCOPE)