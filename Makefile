# PS3 HEN Guitar Controller Remapping Plugin Makefile

# PS3 SDK paths (adjust these to match your PS3 SDK installation)
PS3SDK = /usr/local/ps3dev
PS3DEV = $(PS3SDK)
PSL1GHT = $(PS3SDK)

# Compiler and flags
CC = powerpc64-ps3-elf-gcc
CFLAGS = -Wall -O2 -std=gnu99 -DPS3 \
    -I$(PSL1GHT)/ppu/include
LDFLAGS = -L$(PSL1GHT)/ppu/lib -lsysmodule -lio -lnet -llv2

# Source files
SOURCES = src/guitar_remap.c src/web_interface.c
OBJECTS = $(SOURCES:.c=.o)
TARGET_ELF = guitar_remap.elf
TARGET = guitar_remap.sprx

# Default target
all: $(TARGET)

# Build the plugin
$(TARGET): $(TARGET_ELF)
	sprxlinker $(TARGET_ELF) $(TARGET)
	@echo "Plugin built successfully: $(TARGET)"

$(TARGET_ELF): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) -nostartfiles \
	  /usr/local/ps3dev/ppu/powerpc64-ps3-elf/lib/lv2-sprx.o

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET_ELF) $(TARGET)
	@echo "Build files cleaned"

# Install plugin to PS3 (requires network access)
install: $(TARGET)
	@echo "Copying plugin to PS3..."
	@echo "Please copy $(TARGET) to your PS3's /dev_hdd0/plugins/ directory"
	@echo "Also copy guitar_remap.conf to the same directory"

# Create default configuration
config:
	@echo "Creating default configuration..."
	@mkdir -p /dev_hdd0/plugins/
	@echo "# Guitar Controller Remapping Configuration" > guitar_remap.conf
	@echo "# Format: GUITAR_BUTTON=PS3_BUTTON" >> guitar_remap.conf
	@echo "" >> guitar_remap.conf
	@echo "STRUM_UP=DPAD_UP" >> guitar_remap.conf
	@echo "STRUM_DOWN=DPAD_DOWN" >> guitar_remap.conf
	@echo "FRET_GREEN=CROSS" >> guitar_remap.conf
	@echo "FRET_RED=SQUARE" >> guitar_remap.conf
	@echo "FRET_YELLOW=TRIANGLE" >> guitar_remap.conf
	@echo "FRET_BLUE=CIRCLE" >> guitar_remap.conf
	@echo "FRET_ORANGE=L1" >> guitar_remap.conf
	@echo "WHAMMY=R2" >> guitar_remap.conf
	@echo "STAR_POWER=L2" >> guitar_remap.conf
	@echo "SELECT=SELECT" >> guitar_remap.conf
	@echo "START=START" >> guitar_remap.conf
	@echo "Configuration file created: guitar_remap.conf"

# Build with debug information
debug: CFLAGS += -DDEBUG -g
debug: $(TARGET)

# Build with web interface enabled
web: CFLAGS += -DWEB_INTERFACE
web: $(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the plugin (default)"
	@echo "  clean    - Remove build files"
	@echo "  install  - Install plugin to PS3"
	@echo "  config   - Create default configuration file"
	@echo "  debug    - Build with debug information"
	@echo "  web      - Build with web interface enabled"
	@echo "  help     - Show this help message"

.PHONY: all clean install config debug web help 