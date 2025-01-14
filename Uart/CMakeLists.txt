add_library(Uart OBJECT)
add_library(Uno::Uart ALIAS Uart)

target_include_directories(Uart PUBLIC
        Inc
)

target_sources(Uart PRIVATE
        Src/operator_new.cpp
        Src/ring_buffer.cpp
        Src/scope_lock.cpp
        Src/sw_component.cpp
        Src/sw_uart.cpp
        Src/uart.cpp
        Src/uart_ll.cpp
)
