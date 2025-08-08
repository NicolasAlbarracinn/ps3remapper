# Quick Start Guide - PS3 HEN Guitar Controller Remapping Plugin

This guide will get you up and running in the fastest way possible.

## 🚀 Super Quick Start (If you have PS3 SDK installed)

```bash
# 1. Make the build script executable
chmod +x build_and_install.sh

# 2. Run the automated build and install script
./build_and_install.sh

# 3. Follow the on-screen instructions
```

## 📋 Step-by-Step Quick Start

### Step 1: Install PS3 SDK (One-time setup)

**On Ubuntu/Linux:**
```bash
# Install dependencies
sudo apt-get update
sudo apt-get install build-essential git subversion wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util

# Install PSL1GHT
git clone https://github.com/ps3dev/PSL1GHT.git
cd PSL1GHT
make
sudo make install

# Set up environment
echo 'export PS3DEV=/usr/local/ps3dev' >> ~/.bashrc
echo 'export PSL1GHT=$PS3DEV' >> ~/.bashrc
echo 'export PATH=$PATH:$PS3DEV/host/ppu/bin:$PS3DEV/host/spu/bin' >> ~/.bashrc
source ~/.bashrc
```

**On Windows with WSL:**
```bash
# Open WSL and follow the Ubuntu instructions above
```

### Step 2: Build the Plugin

```bash
# Navigate to plugin directory
cd /path/to/pluginps3

# Build the plugin
make clean && make

# You should see: "Plugin built successfully: guitar_remap.sprx"
```

### Step 3: Transfer to PS3

**Option A: USB Transfer (Easiest)**
1. Format USB drive as FAT32
2. Copy these files to USB:
   - `guitar_remap.sprx`
   - `guitar_remap.conf`
3. Insert USB into PS3
4. Copy files to `/dev_hdd0/plugins/`

**Option B: Network Transfer**
```bash
# If you have network access to PS3
./install.sh
```

### Step 4: Activate Plugin

1. **Restart your PS3**
2. **Load HEN** when PS3 boots
3. **Plugin will auto-load**

### Step 5: Test the Plugin

1. **Connect your guitar controller**
2. **Find your PS3's IP address**:
   ```bash
   ./find_ps3_ip.sh
   ```
3. **Open web browser** and go to: `http://your-ps3-ip:8080`
4. **Press buttons** on your guitar controller and watch the interface

## 🎮 Using the Plugin

### Web Interface
- **Real-time monitoring** of all connected controllers
- **Button press detection** with visual indicators
- **Auto-refreshes** every 2 seconds
- **Mobile-friendly** design

### Console Interface
- **Automatic display** when plugin loads
- **Shows controller status** and button presses
- **Press START** to exit interface

### Configuration
Edit `/dev_hdd0/plugins/guitar_remap.conf` to customize button mappings:
```ini
FRET_GREEN=CROSS
FRET_RED=SQUARE
FRET_YELLOW=TRIANGLE
FRET_BLUE=CIRCLE
FRET_ORANGE=L1
```

## 🔧 Troubleshooting Quick Fixes

### Build Issues
```bash
# Check PS3 SDK
which ppu-gcc

# Reinstall if needed
cd PSL1GHT && make clean && make && sudo make install
```

### Plugin Not Loading
```bash
# Check file permissions
ls -la /dev_hdd0/plugins/guitar_remap*

# Reinstall
rm /dev_hdd0/plugins/guitar_remap.sprx
cp guitar_remap.sprx /dev_hdd0/plugins/
chmod 644 /dev_hdd0/plugins/guitar_remap.sprx
```

### Web Interface Not Working
1. Check PS3 network connection
2. Verify port 8080 is not blocked
3. Try different browser
4. Check firewall settings

## 📱 Mobile Access

You can access the web interface from your phone:
1. **Connect phone to same WiFi** as PS3
2. **Find PS3 IP address** using the finder script
3. **Open phone browser** and go to `http://ps3-ip:8080`
4. **Test guitar controller** and see real-time button detection

## 🎯 What You'll See

### Web Interface Features:
- **Connected Controllers** - All detected controllers
- **Real-time Button Presses** - Live button detection
- **Button History** - Recent button presses
- **Plugin Status** - Active/inactive status
- **Mapping Reference** - Button code guide

### Console Output:
```
==========================================
  PS3 HEN Guitar Controller Remapping
==========================================

Connected Controllers:
----------------------
Port 0: Generic Controller [GUITAR]
  Current: CROSS (0x00000001)
  Recent presses: CROSS SQUARE TRIANGLE

Plugin Status: ACTIVE
Mappings loaded: 12
Web Interface: http://192.168.1.100:8080
```

## 🎸 Testing Your Guitar Controller

1. **Connect guitar controller** to PS3
2. **Open web interface** in browser
3. **Press different buttons** on guitar:
   - Strum bar up/down
   - Fret buttons (green, red, yellow, blue, orange)
   - Whammy bar
   - Star power button
4. **Watch real-time detection** in web interface
5. **Verify button mappings** work correctly

## 🚨 Common Issues & Solutions

| Issue | Solution |
|-------|----------|
| Plugin not building | Install PS3 SDK (PSL1GHT) |
| Plugin not loading | Check file permissions and restart PS3 |
| Web interface not accessible | Check network connection and port 8080 |
| Buttons not responding | Edit configuration file and reload HEN |
| Controller not detected | Check USB connection and try different port |

## 📞 Need Help?

1. **Check the full BUILD_GUIDE.md** for detailed instructions
2. **Review troubleshooting section** in README.md
3. **Try building with debug**: `make debug`
4. **Check system logs** for error messages

## 🎉 Success!

Once everything is working, you'll have:
- ✅ Real-time guitar controller remapping
- ✅ Beautiful web interface for monitoring
- ✅ Configurable button mappings
- ✅ Support for multiple guitar controllers
- ✅ Low-latency input processing

Enjoy your remapped guitar controller! 🎸 