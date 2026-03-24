CC            = $(GCC_PATH)/bin/msp430-elf-g++
OBJCOPY       = $(GCC_PATH)/bin/msp430-elf-objcopy
SIZE          = $(GCC_PATH)/bin/msp430-elf-size
SUPPORT_FILES = $(GCC_PATH)/include

MCU           = msp430g2553
TARGET        = main
SRCS          = main.cpp
UC1677PATH    = ../../../include

CFLAGS  = -mmcu=$(MCU) -I$(SUPPORT_FILES) -L$(SUPPORT_FILES) -I$(UC1677PATH) -std=c++11 -O2 -fno-exceptions -fno-rtti -Wall -Wextra

all: $(TARGET).elf
	@$(SIZE) $(TARGET).elf

$(TARGET).elf: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET).elf

flash: all
	mspdebug rf2500 "prog $(TARGET).elf"

clean:
	rm -f $(TARGET).elf