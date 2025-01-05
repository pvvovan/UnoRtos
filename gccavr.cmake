set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_ASM_COMPILER_FORCED TRUE)
set(CMAKE_LINKER_FORCED TRUE)

set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)
set(CMAKE_ASM_COMPILER_ID GNU)
set(CMAKE_LINKER_ID GNU)

set(CMAKE_C_COMPILER ${GCC_PATH}avr-gcc)
set(CMAKE_CXX_COMPILER ${GCC_PATH}avr-g++)
set(CMAKE_ASM_COMPILER ${GCC_PATH}avr-gcc)
set(CMAKE_LINKER_ID ${GCC_PATH}avr-g++)

set(CMAKE_EXECUTABLE_SUFFIX_C .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)
set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)

add_compile_options(
        -mmcu=${MCU}
)

add_link_options(
        -mmcu=${MCU}
)