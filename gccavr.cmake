set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_ASM_COMPILER_FORCED TRUE)
set(CMAKE_LINKER_FORCED TRUE)

set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)
set(CMAKE_ASM_COMPILER_ID GNU)
set(CMAKE_LINKER_ID GNU)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_ASM_COMPILER avr-gcc)
set(CMAKE_LINKER avr-g++)

set(CMAKE_EXECUTABLE_SUFFIX_C .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)
set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)

add_compile_options(
        -mmcu=${MCU}
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        "$<$<COMPILE_LANGUAGE:ASM>:-x;assembler-with-cpp>"
        $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
)

add_link_options(
        -mmcu=${MCU}
        -Wl,--print-memory-usage
)
