# PS3 HEN Guitar Controller Remapping Plugin

A PlayStation 3 HEN (Homebrew ENabler) plugin that allows you to remap buttons on a generic guitar controller that the PS3 recognizes as a generic controller. **Now with webMAN MOD integration!**

## Features

- **Real-time button remapping** - No system restart required
- **Configurable button mappings** - Easy to customize via config file
- **Multiple guitar controller support** - Works with various generic guitar controllers
- **Low-latency processing** - Optimized for gaming performance
- **🎮 Controller Monitoring Interface** - See all connected controllers and their button presses
- **🌐 webMAN MOD Integration** - Access controller monitoring through webMAN MOD interface
- **📊 Real-time Input Detection** - Watch how your guitar controller inputs are recognized by the PS3

## Requirements

- PS3 with HEN (Homebrew ENabler) installed
- Generic guitar controller (USB or wireless)
- USB storage device for installation
- Network connection (for web interface)
- **webMAN MOD** (optional, for integrated interface)

## Installation

1. Copy files to your PS3 (FTP or file manager):
   - `guitar_remap.sprx` → `/dev_hdd0/plugins/`
   - `guitar_remap.conf` → `/dev_hdd0/plugins/`

2. Enable the plugin (pick one):
   - webMAN MOD: open `http://your-ps3-ip/setup.ps3` → Plugin Setup → add `/dev_hdd0/plugins/guitar_remap.sprx` → Save → Reboot
   - boot_plugins.txt: edit `/dev_hdd0/boot_plugins.txt` and add a line:
     - `/dev_hdd0/plugins/guitar_remap.sprx` → Reboot

3. After reboot, the plugin loads and starts remapping per your config.

## Using the Interface

### webMAN MOD Integration (Recommended)
If you have **webMAN MOD** installed, the plugin will integrate seamlessly:

1. **Access through webMAN MOD**:
   ```
   http://your-ps3-ip/guitar_remap
   ```
   Example: `http://192.168.0.28/guitar_remap`

2. **Features**:
   - **Integrated with webMAN MOD** - Same look and feel
   - **Navigation buttons** - Easy access back to webMAN MOD
   - **Dark theme** - Matches webMAN MOD styling
   - **Responsive design** - Works on all devices

### Standalone Web Interface
If webMAN MOD is not available, the plugin falls back to standalone mode:

1. **Access standalone interface**:
   ```
   http://your-ps3-ip:8080/guitar_remap
   ```

### Console Interface
The plugin automatically starts a console interface that shows:
- All connected controllers
- Real-time button press detection
- Current button states
- Button press history
- Plugin status

**Controls:**
- Press any button to see input detection
- Press START to exit interface
- Press SELECT to refresh

### Uninstall / Disable
- webMAN MOD: remove the line from Plugin Setup → Save → Reboot
- boot_plugins.txt: remove the line from `/dev_hdd0/boot_plugins.txt` → Reboot

## Configuration

Edit the `guitar_remap.conf` file to customize button mappings:

```ini
[GuitarController]
# Strum buttons
STRUM_UP=DPAD_UP
STRUM_DOWN=DPAD_DOWN

# Fret buttons
FRET_GREEN=CROSS
FRET_RED=SQUARE
FRET_YELLOW=TRIANGLE
FRET_BLUE=CIRCLE
FRET_ORANGE=L1

# Special buttons
WHAMMY=R2
STAR_POWER=L2
SELECT=SELECT
START=START

# D-pad for menu navigation
DPAD_UP=DPAD_UP
DPAD_DOWN=DPAD_DOWN
DPAD_LEFT=DPAD_LEFT
DPAD_RIGHT=DPAD_RIGHT
```

## Button Mapping Reference

### Standard PS3 Controller Buttons
- `CROSS` - X button
- `SQUARE` - Square button
- `TRIANGLE` - Triangle button
- `CIRCLE` - Circle button
- `L1` - Left shoulder button
- `L2` - Left trigger
- `R1` - Right shoulder button
- `R2` - Right trigger
- `SELECT` - Select button
- `START` - Start button
- `DPAD_UP` - D-pad up
- `DPAD_DOWN` - D-pad down
- `DPAD_LEFT` - D-pad left
- `DPAD_RIGHT` - D-pad right

### Guitar Controller Buttons
- `STRUM_UP` - Strum bar up
- `STRUM_DOWN` - Strum bar down
- `FRET_GREEN` - Green fret button
- `FRET_RED` - Red fret button
- `FRET_YELLOW` - Yellow fret button
- `FRET_BLUE` - Blue fret button
- `FRET_ORANGE` - Orange fret button
- `WHAMMY` - Whammy bar
- `STAR_POWER` - Star power button

## Troubleshooting

1. **Controller not detected**: Ensure your guitar controller is properly connected and recognized by the PS3
2. **Buttons not responding**: Check the configuration file for correct button mappings
3. **Plugin not loading**: Verify the plugin file is in the correct directory and HEN is properly installed
4. **Web interface not accessible**: 
   - **webMAN MOD mode**: Check that webMAN MOD is running and accessible
   - **Standalone mode**: Check network connection and port 8080
5. **Interface not showing**: Restart your PS3 or reload HEN to ensure the plugin loads properly

## webMAN MOD Compatibility

### Integration Features
- **Automatic detection** - Plugin detects if webMAN MOD is running
- **Port sharing** - Uses webMAN MOD's port 80 when available
- **Fallback mode** - Automatically falls back to port 8080 if needed
- **Unified interface** - Seamless integration with webMAN MOD

### Access URLs
- **With webMAN MOD**: `http://your-ps3-ip/guitar_remap`
- **Without webMAN MOD**: `http://your-ps3-ip:8080/guitar_remap`

### Navigation
- **Back to webMAN MOD** - Use the "🏠 Back to webMAN MOD" button
- **Refresh interface** - Use the "🔄 Refresh" button
- **Auto-refresh** - Interface updates every 3 seconds

## Development / Build

Fastest path (Docker, Windows):

1) Install Docker Desktop and share the `D:` drive
2) Build using the local SDK image (created once in this repo history):

```bash
docker run --rm -v "D:/src/pluginps3:/src" ps3sdk-local bash -lc "pacman -S --noconfirm make || true; cd /src && make clean && make -j1"
```

Artifacts: `guitar_remap.sprx` will appear in the project root.

If you don't have `ps3sdk-local`:

```bash
docker build -t ps3sdk-local ./ps3sdk-docker
```

Common targets:
- `make` - Build release
- `make clean` - Clean artifacts

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests. 