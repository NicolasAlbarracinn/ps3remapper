# PS3 HEN Guitar Controller Remapping Plugin - Build & Installation Guide

This guide will walk you through compiling and installing the plugin on your PS3.

## Prerequisites

### 1. PS3 Requirements
- PS3 with HEN (Homebrew ENabler) installed
- USB storage device (for transferring files)
- Network connection (for web interface)

### 2. Development Environment
You have two options for building:

#### Option A: Build on Linux/Ubuntu (Recommended)
- Ubuntu 18.04+ or similar Linux distribution
- PS3 SDK (PSL1GHT) installed

#### Option B: Build on Windows with WSL
- Windows 10/11 with WSL (Windows Subsystem for Linux)
- Ubuntu installed in WSL

## Step 1: Install PS3 SDK (PSL1GHT)

### On Ubuntu/Linux:
```bash
# Install dependencies
sudo apt-get update
sudo apt-get install build-essential git subversion wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util

# Clone and build PSL1GHT
git clone https://github.com/ps3dev/PSL1GHT.git
cd PSL1GHT
make
sudo make install

# Set up environment variables
echo 'export PS3DEV=/usr/local/ps3dev' >> ~/.bashrc
echo 'export PSL1GHT=$PS3DEV' >> ~/.bashrc
echo 'export PATH=$PATH:$PS3DEV/host/ppu/bin:$PS3DEV/host/spu/bin' >> ~/.bashrc
source ~/.bashrc
```

### On Windows with WSL:
```bash
# Open WSL and follow the Ubuntu instructions above
# Make sure to use Ubuntu 18.04+ in WSL
```

## Step 2: Download and Prepare the Plugin

```bash
# Clone or download the plugin source code
# If you have the files locally, navigate to the plugin directory
cd /path/to/pluginps3

# Make sure all files are present
ls -la
# You should see: src/, Makefile, README.md, etc.
```

## Step 3: Build the Plugin

```bash
# Clean any previous builds
make clean

# Build the plugin
make

# If successful, you should see:
# Plugin built successfully: guitar_remap.sprx
```

### Build Options:
```bash
# Build with debug information
make debug

# Build with web interface enabled
make web

# Show all build options
make help
```

## Step 4: Prepare Installation Files

```bash
# Create a directory for installation files
mkdir ps3_installation
cp guitar_remap.sprx ps3_installation/
cp guitar_remap.conf ps3_installation/
cp install.sh ps3_installation/
cp find_ps3_ip.sh ps3_installation/
cp README.md ps3_installation/

# Make scripts executable
chmod +x ps3_installation/*.sh
```

## Step 5: Transfer to PS3

### Method A: USB Transfer (Recommended)
1. **Format USB drive** as FAT32
2. **Copy installation files** to USB:
   ```bash
   cp -r ps3_installation/* /path/to/usb/ps3_plugins/
   ```
3. **Insert USB** into PS3
4. **Navigate to USB** in PS3 file manager
5. **Copy files** to PS3 internal storage

### Method B: Network Transfer
1. **Enable FTP** on PS3 (if available)
2. **Connect via FTP** from your computer
3. **Upload files** to `/dev_hdd0/plugins/`

### Method C: Direct Installation
If you have network access to PS3:
```bash
# Use the install script (requires network access)
./install.sh
```

## Step 6: Install on PS3

### Using the Install Script:
1. **Connect to PS3** via SSH or terminal
2. **Navigate to installation directory**
3. **Run install script**:
   ```bash
   cd /path/to/installation/files
   chmod +x install.sh
   ./install.sh
   ```

### Manual Installation:
1. **Create plugins directory** (if it doesn't exist):
   ```bash
   mkdir -p /dev_hdd0/plugins
   ```

2. **Copy plugin files**:
   ```bash
   cp guitar_remap.sprx /dev_hdd0/plugins/
   cp guitar_remap.conf /dev_hdd0/plugins/
   ```

3. **Set permissions**:
   ```bash
   chmod 644 /dev_hdd0/plugins/guitar_remap.sprx
   chmod 644 /dev_hdd0/plugins/guitar_remap.conf
   ```

## Step 7: Activate the Plugin

### Restart PS3 Method:
1. **Restart your PS3** completely
2. **Load HEN** when PS3 boots
3. **Plugin will auto-load** with HEN

### Reload HEN Method:
1. **Go to HEN settings** on PS3
2. **Reload HEN** without restarting
3. **Plugin should load** automatically

## Step 8: Test the Plugin

### Check if Plugin is Running:
1. **Connect your guitar controller** to PS3
2. **Look for console output** (if available)
3. **Check web interface** at `http://your-ps3-ip:8080`

### Using the Web Interface:
1. **Find your PS3's IP address**:
   ```bash
   ./find_ps3_ip.sh
   ```

2. **Open web browser** and go to:
   ```
   http://your-ps3-ip:8080
   ```

3. **Test controller inputs** and see real-time detection

### Using the Console Interface:
1. **Access PS3 terminal** (if available)
2. **Look for plugin output** showing:
   - Connected controllers
   - Button press detection
   - Plugin status

## Step 9: Configure Button Mappings

### Edit Configuration:
1. **Open configuration file**:
   ```bash
   nano /dev_hdd0/plugins/guitar_remap.conf
   ```

2. **Modify button mappings** as needed:
   ```ini
   FRET_GREEN=CROSS
   FRET_RED=SQUARE
   # etc.
   ```

3. **Save and restart** plugin or reload HEN

### Test Mappings:
1. **Press buttons** on your guitar controller
2. **Watch web interface** for button detection
3. **Verify mappings** work correctly in games

## Troubleshooting

### Build Issues:
```bash
# Check PS3 SDK installation
which ppu-gcc
ppu-gcc --version

# Reinstall SDK if needed
cd PSL1GHT
make clean
make
sudo make install
```

### Installation Issues:
```bash
# Check file permissions
ls -la /dev_hdd0/plugins/

# Reinstall plugin
rm /dev_hdd0/plugins/guitar_remap.sprx
cp guitar_remap.sprx /dev_hdd0/plugins/
chmod 644 /dev_hdd0/plugins/guitar_remap.sprx
```

### Plugin Not Loading:
1. **Check HEN installation**
2. **Verify file locations**
3. **Restart PS3 completely**
4. **Check system logs**

### Web Interface Not Working:
1. **Check PS3 network connection**
2. **Verify port 8080 is not blocked**
3. **Check firewall settings**
4. **Try different browser**

## Quick Start Commands

```bash
# Complete build and install (if you have network access)
make clean && make && ./install.sh

# Check plugin status
ls -la /dev_hdd0/plugins/guitar_remap*

# Find PS3 IP for web interface
./find_ps3_ip.sh

# Test web interface
curl http://your-ps3-ip:8080
```

## Support

If you encounter issues:
1. **Check the troubleshooting section**
2. **Review system logs**
3. **Verify all prerequisites are met**
4. **Try building with debug flags**: `make debug` 