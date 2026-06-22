# 1. Переменные кросс-компилятора под ARM
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Флаги компиляции для чистого bare-metal
CFLAGS  = -mcpu=cortex-m4 -mthumb -O0 -g -Wall
CFLAGS += -ffreestanding -nostdlib --specs=nosys.specs -Iinclude

# Имена файлов
TARGET        = blink
LINKER_SCRIPT = linker.ld

# Список исходных файлов
SRCS = src/startup_stm32f446xx.s src/main.c

# 2. Главные цели
.PHONY: all flash clean

all: $(TARGET).bin

# Генерация чистого бинарника из ELF
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
	@echo "🔥 Сборка завершена! Прошивка $(TARGET).bin готова."

# Линковка и компиляция
$(TARGET).elf: $(SRCS) $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) -T$(LINKER_SCRIPT) $(SRCS) -o $(TARGET).elf

# 3. Команда для прошивки платы
flash: all
	st-flash write $(TARGET).bin 0x08000000

# 4. Очистка
clean:
	rm -f $(TARGET).elf $(TARGET).bin
