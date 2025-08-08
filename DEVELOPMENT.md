# Development Guide

This document provides information for developers who want to modify or extend the PS3 HEN Guitar Controller Remapping Plugin.

## Project Structure

```
pluginps3/
├── src/
│   ├── guitar_remap.c      # Main plugin source code
│   └── guitar_remap.h      # Header file with definitions
├── guitar_remap.conf       # Default configuration file
├── Makefile               # Build configuration
├── install.sh             # Installation script
├── README.md              # User documentation
└── DEVELOPMENT.md         # This file
```

## Prerequisites

To develop this plugin, you'll need:

1. **PS3 SDK (PSL1GHT)**: Install the PS3 development kit
2. **Cross-compiler**: ppu-gcc for PowerPC compilation
3. **Development environment**: Linux or WSL recommended

### Installing PS3 SDK

```bash
# Clone PSL1GHT
git clone https://github.com/ps3dev/PSL1GHT.git
cd PSL1GHT

# Install dependencies (Ubuntu/Debian)
sudo apt-get install build-essential git subversion wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util

# Build and install
make
sudo make install
```

## Building the Plugin

1. **Set up environment**:
   ```bash
   export PS3DEV=/usr/local/ps3dev
   export PSL1GHT=$PS3DEV
   export PATH=$PATH:$PS3DEV/host/ppu/bin:$PS3DEV/host/spu/bin
   ```

2. **Build the plugin**:
   ```bash
   make clean
   make
   ```

3. **Install to PS3**:
   ```bash
   make install
   ```

## Code Architecture

### Main Components

1. **Configuration System** (`load_config()`)
   - Reads button mappings from `guitar_remap.conf`
   - Supports key=value format
   - Auto-creates default config if missing

2. **Button Mapping** (`remap_buttons()`)
   - Translates guitar controller buttons to PS3 buttons
   - Real-time remapping without system restart
   - Configurable mappings

3. **Thread Management** (`remap_controller_thread()`)
   - Background thread for continuous remapping
   - Low-latency input processing
   - Graceful shutdown support

### Key Data Structures

```c
// Button mapping structure
typedef struct {
    int guitar_button;    // Guitar controller button code
    int ps3_button;       // PS3 controller button code
    char name[32];        // Human-readable button name
} button_mapping_t;
```

### Button Codes

#### Guitar Controller Buttons
- `GUITAR_STRUM_UP`: Strum bar up
- `GUITAR_STRUM_DOWN`: Strum bar down
- `GUITAR_FRET_GREEN`: Green fret button
- `GUITAR_FRET_RED`: Red fret button
- `GUITAR_FRET_YELLOW`: Yellow fret button
- `GUITAR_FRET_BLUE`: Blue fret button
- `GUITAR_FRET_ORANGE`: Orange fret button
- `GUITAR_WHAMMY`: Whammy bar
- `GUITAR_STAR_POWER`: Star power button

#### PS3 Controller Buttons
- `PS3_CROSS`: X button
- `PS3_SQUARE`: Square button
- `PS3_TRIANGLE`: Triangle button
- `PS3_CIRCLE`: Circle button
- `PS3_L1`: Left shoulder button
- `PS3_L2`: Left trigger
- `PS3_R1`: Right shoulder button
- `PS3_R2`: Right trigger
- `PS3_SELECT`: Select button
- `PS3_START`: Start button
- `PS3_DPAD_UP`: D-pad up
- `PS3_DPAD_DOWN`: D-pad down
- `PS3_DPAD_LEFT`: D-pad left
- `PS3_DPAD_RIGHT`: D-pad right

## Adding New Features

### Adding New Button Types

1. **Define the button code** in `guitar_remap.h`:
   ```c
   #define GUITAR_NEW_BUTTON 0x00000200
   ```

2. **Add parsing support** in `parse_button_name()`:
   ```c
   if (strcmp(name, "NEW_BUTTON") == 0) return GUITAR_NEW_BUTTON;
   ```

3. **Update documentation** in `README.md` and `guitar_remap.conf`

### Adding New PS3 Button Types

1. **Define the button code** in `guitar_remap.h`:
   ```c
   #define PS3_NEW_BUTTON 0x00004000
   ```

2. **Add parsing support** in `parse_ps3_button()`:
   ```c
   if (strcmp(name, "NEW_BUTTON") == 0) return PS3_NEW_BUTTON;
   ```

### Adding Configuration Options

1. **Add new configuration parameters** to the config structure
2. **Update `load_config()`** to parse new parameters
3. **Add default values** in `create_default_config()`

## Debugging

### Enable Debug Output

Add debug prints to the code:

```c
#ifdef DEBUG
    printf("[DEBUG] Button pressed: %s\n", button_name);
#endif
```

### Testing

1. **Compile with debug flags**:
   ```bash
   make CFLAGS="-Wall -O2 -std=c99 -DPS3 -DDEBUG"
   ```

2. **Test on PS3**:
   - Install the plugin
   - Connect guitar controller
   - Check for debug output in system logs

### Common Issues

1. **Plugin not loading**: Check file permissions and HEN installation
2. **Buttons not responding**: Verify button mappings in config file
3. **Performance issues**: Adjust thread sleep time in `remap_controller_thread()`

## Contributing

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/new-feature`
3. **Make your changes**
4. **Test thoroughly** on a PS3 with HEN
5. **Submit a pull request**

### Code Style

- Use consistent indentation (4 spaces)
- Follow C99 standard
- Add comments for complex logic
- Use descriptive variable names
- Keep functions small and focused

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Support

For development questions or issues:

1. Check the existing issues on GitHub
2. Review the PS3 SDK documentation
3. Consult the PS3 HEN community forums
4. Create a new issue with detailed information 