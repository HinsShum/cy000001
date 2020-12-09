# @file lib/st/stm32f1xx/STM32F1xx_HAL_Driver/Src/CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2020/11/25 21:25:45
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

set(C_SOURCE_FILES "stm32f1xx_ll_utils.c;stm32f1xx_ll_rcc.c;stm32f1xx_ll_gpio.c")
set(TARGET_LIB_NAME stlib)

add_library(${TARGET_LIB_NAME} STATIC ${C_SOURCE_FILES})
set(C_SOURCE_LIBS "${C_SOURCE_LIBS};${TARGET_LIB_NAME}" PARENT_SCOPE)

target_include_directories(${TARGET_LIB_NAME} PRIVATE ${G_SOURCE_INCLUDE_DIRS})