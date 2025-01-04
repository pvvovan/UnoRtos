cmake_minimum_required(VERSION 3.28)
set(MCU atmega328p)
project(uno_rtos C CXX ASM)

add_executable(${PROJECT_NAME}
        Uart/Src/operator_new.cpp
        Uart/Src/ring_buffer.cpp
        Uart/Src/scope_lock.cpp
        Uart/Src/sw_component.cpp
        Uart/Src/sw_uart.cpp
        Uart/Src/uart.cpp
        Uart/Src/uart_ll.cpp

        Src/main.c
        Src/app.c
        Src/gpio.c
        FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega/port.c
        FreeRTOS-Kernel/tasks.c
        FreeRTOS-Kernel/queue.c
        FreeRTOS-Kernel/list.c
        FreeRTOS-Kernel/portable/MemMang/heap_1.c

        Src/protected_io.S
)

target_include_directories(${PROJECT_NAME} PRIVATE
        Inc
        Uart/Inc
        FreeRTOS-Kernel/include
        FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        F_CPU=16000000UL
)

set_source_files_properties(
        Src/protected_io.S
        PROPERTIES COMPILE_OPTIONS
        "-x;assembler-with-cpp"
)

set_source_files_properties(
        FreeRTOS-Kernel/tasks.c
        FreeRTOS-Kernel/portable/MemMang/heap_1.c
        PROPERTIES COMPILE_OPTIONS
        "-Wno-pointer-to-int-cast;-Wno-int-to-pointer-cast"
)

set_source_files_properties(
        FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega/port.c
        PROPERTIES COMPILE_OPTIONS
        "-Wno-cpp"
)

add_custom_target(flash
        avrdude -p ${MCU} -c usbtiny -U flash:w:${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf:e
)
