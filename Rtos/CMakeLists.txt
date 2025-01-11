cmake_minimum_required(VERSION 3.28)
project(Rtos C)
add_library(${PROJECT_NAME} OBJECT)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        FreeRTOS-Kernel/include
        FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega
)

target_sources(${PROJECT_NAME} PRIVATE
        FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega/port.c
        FreeRTOS-Kernel/tasks.c
        FreeRTOS-Kernel/queue.c
        FreeRTOS-Kernel/list.c
        FreeRTOS-Kernel/portable/MemMang/heap_1.c
)

set_source_files_properties(
        FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega/port.c
        PROPERTIES COMPILE_OPTIONS
        -Wno-conversion
)

set_source_files_properties(
        FreeRTOS-Kernel/tasks.c
        FreeRTOS-Kernel/portable/MemMang/heap_1.c
        PROPERTIES COMPILE_OPTIONS
        "-Wno-pointer-to-int-cast;-Wno-int-to-pointer-cast;-Wno-conversion"
)
