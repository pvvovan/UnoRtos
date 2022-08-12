PROJECT = app

C_SRC = \
Src/main.c \
Src/app.c \
Src/gpio.c

CXX_SRC =

ASM_SRC =

INCLUDEDIRS = -iquote . \
-I Inc

OUT = out

CC = avr-gcc
CXX = avr-g++
AS = avr-gcc -x assembler-with-cpp
OBJCOPY = avr-objcopy

CC_FLAGS = -mmcu=atmega328p -Wall -Wextra ${INCLUDEDIRS}

# Generate dependency information
CC_FLAGS += -MD -MP -MF"$(@:%.o=%.d)"

CFLAGS = ${CC_FLAGS} -std=gnu99
CXXFLAGS = ${CC_FLAGS} -std=gnu++17
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
	$(CC) $(OBJ_FILES) -o $@

$(OUT)/$(PROJECT).bin: $(OUT)/$(PROJECT).elf Makefile
	$(OBJCOPY) -O binary $< $@

.PHONY: clean
clean:
	rm -f $(OUT)/*


-include $(DEPS)
