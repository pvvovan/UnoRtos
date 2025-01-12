cmake_minimum_required(VERSION 3.28)
set(MCU atmega328p)
project(uno_rtos C CXX ASM)

add_executable(${PROJECT_NAME}
        Src/main.c
        Src/app.c
        Src/gpio.c
        Src/protected_io.S
)

target_include_directories(${PROJECT_NAME} PRIVATE
        Inc
)

add_compile_definitions(
        F_CPU=16000000UL
)

add_subdirectory(Rtos)
add_subdirectory(Uart)
target_link_libraries(${PROJECT_NAME} PRIVATE Rtos Uart)

add_custom_target(flash
        avrdude -p ${MCU} -c usbtiny -U flash:w:${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf:e
)
