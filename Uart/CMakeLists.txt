cmake_minimum_required(VERSION 3.28)
project(Uart CXX)
add_library(${PROJECT_NAME} OBJECT)

target_include_directories(${PROJECT_NAME} PUBLIC
        Inc
)

target_sources(${PROJECT_NAME} PRIVATE
        Src/operator_new.cpp
        Src/ring_buffer.cpp
        Src/scope_lock.cpp
        Src/sw_component.cpp
        Src/sw_uart.cpp
        Src/uart.cpp
        Src/uart_ll.cpp
)
