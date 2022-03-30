NAME=vector-test
MCU=atmega328p
F_CPU=16000000ul

PROGRAMMER=arduino
AVRDUDE_FLAGS= -P/dev/ttyUSB0 -b57600

ifeq ($(STD),)
STD=c++17
endif

BUILD_DIR=./build
LIB_DIR=../..
COMMON_DIR=../common

INCLUDES=-I$(COMMON_DIR) -I$(LIB_DIR)/include

SOURCES=$(wildcard *.cpp $(LIB_DIR)/src/*.cc $(COMMON_DIR)/*.cpp)
VPATH=.:$(LIB_DIR)/src:$(COMMON_DIR)
OBJECTS=$(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES:%=%.o)))

CXXFLAGS=-std=$(STD) -O2 -Wall -Wextra -pedantic -fno-exceptions -fno-rtti -fno-unwind-tables -fno-threadsafe-statics -Wshadow -Wcast-qual -Wpointer-arith -Wundef -DF_CPU=$(F_CPU)
LDFLAGS=

TARGET=$(BUILD_DIR)/$(NAME)

all: hex size

hex: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -j .data -j .text $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(OBJECTS)
	avr-g++ $(LDFLAGS) -mmcu=$(MCU) $(OBJECTS) -o $(TARGET).elf

$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	avr-g++ -c $(CXXFLAGS) -mmcu=$(MCU) $(INCLUDES) $< -o $@

$(BUILD_DIR)/%.cc.o: %.cc
	@mkdir -p $(BUILD_DIR)
	avr-g++ -c $(CXXFLAGS) -mmcu=$(MCU) $(INCLUDES) $< -o $@

size: $(TARGET).elf
	avr-objdump -Pmem-usage $(TARGET).elf

program: $(TARGET).hex
	avrdude -p$(MCU) $(AVRDUDE_FLAGS) -c$(PROGRAMMER) -Uflash:w:$(TARGET).hex:a

clean:
	rm -rf $(BUILD_DIR)/*.o
	rm -rf $(BUILD_DIR)/*.elf
	rm -rf $(BUILD_DIR)/*.hex
