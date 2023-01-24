set(ProjectId "FreeRTOS_003LEDsNotify")
cmake_minimum_required(VERSION 3.15.3)

#Constants
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")

#Included files
file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE Sources_FreeRTOS ${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/FreeRTOS/*.c)
file(GLOB_RECURSE Sources_SEGGER ${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/SEGGER/*.c)
file(GLOB_RECURSE Sources_SEGGER_asm ${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/SEGGER/*.S)
list(APPEND Sources ${Sources_FreeRTOS})
list(APPEND Sources ${Sources_SEGGER})
list(APPEND Sources ${Sources_SEGGER_asm})
list(FILTER Sources EXCLUDE REGEX "heap_1.c")
list(FILTER Sources EXCLUDE REGEX "heap_2.c")
list(FILTER Sources EXCLUDE REGEX "heap_3.c")
list(FILTER Sources EXCLUDE REGEX "heap_5.c")

#Import toolchain
set(CMAKE_TOOLCHAIN_FILE "arm_toolchain.cmake")

#Configure project
project(${ProjectId} C ASM)

#Includes
include_directories(${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/cfg)
file(GLOB_RECURSE Includes ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h) #Find all .h
foreach(Include IN LISTS Includes)
    get_filename_component(IncludeDir ${Include} DIRECTORY) #Get the include path
    list(APPEND IncludeDirs ${IncludeDir})
endforeach()
list(REMOVE_DUPLICATES IncludeDirs) #Remove duplicates if any
include_directories(${IncludeDirs}) #Include found directories
#Includes for FreeRTOS
include_directories(${CMAKE_CURRENT_LIST_DIR}/../ThirdParty/FreeRTOS)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../ThirdParty/FreeRTOS/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F)
#Includes for SEGGER Sysview
include_directories(${CMAKE_CURRENT_LIST_DIR}/../ThirdParty/SEGGER/SEGGER)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../ThirdParty/SEGGER/OS)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../ThirdParty/SEGGER/Config)

#Target executable
add_executable(${ProjectId} ${Sources})
set_target_properties(
    ${ProjectId}
    PROPERTIES
        OUTPUT_NAME "${ProjectId}"
        SUFFIX ".elf"
)

#Post hook
add_custom_command(
    TARGET ${ProjectId}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${ProjectId}.elf ${ProjectId}.hex
)
