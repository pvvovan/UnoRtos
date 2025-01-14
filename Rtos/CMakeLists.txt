add_library(Rtos OBJECT)
add_library(Uno::Rtos ALIAS Rtos)

target_include_directories(Rtos PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        FreeRTOS-Kernel/include
        FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega
)

target_sources(Rtos PRIVATE
        FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega/port.c
        FreeRTOS-Kernel/tasks.c
        FreeRTOS-Kernel/queue.c
        FreeRTOS-Kernel/list.c
        FreeRTOS-Kernel/portable/MemMang/heap_1.c
)

set_source_files_properties(
        FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega/port.c
        PROPERTIES COMPILE_OPTIONS
        "-Wno-conversion;-Wno-pedantic;-Wno-cpp"
)

set_source_files_properties(
        FreeRTOS-Kernel/tasks.c
        FreeRTOS-Kernel/portable/MemMang/heap_1.c
        PROPERTIES COMPILE_OPTIONS
        "-Wno-pointer-to-int-cast;-Wno-int-to-pointer-cast;-Wno-conversion"
)
