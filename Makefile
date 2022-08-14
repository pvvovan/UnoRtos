PROJECT = app
MCU = atmega328p

C_SRC = \
Src/main.c \
Src/app.c \
Src/gpio.c \
FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega/port.c \
FreeRTOS-Kernel/tasks.c \
FreeRTOS-Kernel/queue.c \
FreeRTOS-Kernel/list.c \
FreeRTOS-Kernel/portable/MemMang/heap_1.c

CXX_SRC =

ASM_SRC =

INCLUDEDIRS = \
-iquote Inc \
-I FreeRTOS-Kernel/include \
-I FreeRTOS-Kernel/portable/ThirdParty/GCC/ATmega

OUT = out

CC = avr-gcc
CXX = avr-g++
AS = avr-gcc -x assembler-with-cpp
OBJCOPY = avr-objcopy
SIZE = avr-size

CC_FLAGS = -mmcu=$(MCU) -Wall -Wextra $(INCLUDEDIRS) -D F_CPU=16000000UL -O2 -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

# Generate dependency information
CC_FLAGS += -MD -MP -MF"$(@:%.o=%.d)"

CFLAGS = $(CC_FLAGS) -std=gnu99
CXXFLAGS = $(CC_FLAGS) -std=gnu++17
ASFLAGS =

OBJ_FILES = $(addprefix $(OUT)/, $(notdir $(ASM_SRC:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SRC)))

OBJ_FILES += $(addprefix $(OUT)/, $(notdir $(C_SRC:.c=.o)))
vpath %.c $(sort $(dir $(C_SRC)))

OBJ_FILES += $(addprefix $(OUT)/, $(notdir $(CXX_SRC:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CXX_SRC)))

DEPS = $(OBJ_FILES:.o=.d)

# unconditionally ensure output directory
$(shell test -d $(OUT) || mkdir $(OUT))

all: $(OUT)/$(PROJECT).bin

$(OUT)/%.o: %.c Makefile
	@echo CC $<
	@$(CC) -c $(CFLAGS) $< -o $@

$(OUT)/%.o: %.cpp Makefile
	@echo CXX $<
	@$(CXX) -c $(CXXFLAGS) $< -o $@

$(OUT)/%.o: %.S Makefile
	@echo AS $<
	$(AS) -c $(ASFLAGS) $< -o $@

$(OUT)/$(PROJECT).elf: $(OBJ_FILES) Makefile
	$(CC) $(OBJ_FILES) -o $@ $(CC_FLAGS)
	$(SIZE) $@

$(OUT)/$(PROJECT).bin: $(OUT)/$(PROJECT).elf Makefile
	$(OBJCOPY) -O binary $< $@

.PHONY: clean
clean:
	rm -f -r $(OUT)


flash: $(OUT)/$(PROJECT).elf
	avrdude -p $(MCU) -c usbtiny -U flash:w:$(OUT)/$(PROJECT).elf:e


-include $(DEPS)
