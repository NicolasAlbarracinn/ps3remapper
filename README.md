# PS3 Plugin Development Setup Guide

## Prerequisites
- Windows 10/11 with WSL support
- Git Bash (alternative if WSL fails)

## Step 1: Install WSL (Windows Subsystem for Linux)

### Option A: Automatic Installation
```bash
wsl --install -d Ubuntu
```

### Option B: Manual Installation (if automatic fails)
1. **Enable Windows Features** (run PowerShell as Administrator):
```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

2. **Restart your computer**

3. **Install WSL**:
```bash
wsl --install -d Ubuntu
```

### Troubleshooting WSL Installation
- **Error: HCS_E_SERVICE_NOT_AVAILABLE**: Enable Windows features first
- **Error: TRUST_E_BAD_DIGEST**: Clear WSL cache and retry
- **Permission errors**: Run PowerShell as Administrator

## Step 2: Install Required Dependencies

Once WSL is running, install the necessary build tools:

```bash
# Update package lists
sudo apt update

# Install essential build tools
sudo apt install -y git build-essential cmake python3 curl

# Install additional dependencies for PS3 toolchain
sudo apt install -y bison flex autoconf automake libtool pkg-config

# Install Python development headers
sudo apt install -y python3-dev python-is-python3
```

## Step 3: Set Up PS3 Development Environment

### Create Required Directories
```bash
# Create PS3 development directories
sudo mkdir -p /usr/local/ps3dev
sudo mkdir -p /usr/local/psl1ght

# Set proper ownership
sudo chown -R $USER:$USER /usr/local/ps3dev
sudo chown -R $USER:$USER /usr/local/psl1ght
```

### Set Environment Variables
```bash
# Set PS3 development paths
export PS3DEV=/usr/local/ps3dev
export PSL1GHT=/usr/local/psl1ght

# Add to PATH
export PATH=$PATH:/usr/local/ps3dev/bin:/usr/local/ps3dev/ppu/bin:/usr/local/ps3dev/spu/bin

# Make permanent (add to ~/.bashrc)
echo 'export PS3DEV=/usr/local/ps3dev' >> ~/.bashrc
echo 'export PSL1GHT=/usr/local/psl1ght' >> ~/.bashrc
echo 'export PATH=$PATH:/usr/local/ps3dev/bin:/usr/local/ps3dev/ppu/bin:/usr/local/ps3dev/spu/bin' >> ~/.bashrc
source ~/.bashrc
```

### Alternative Environment Setup (Recommended)
```bash
# Pick the standard path
export PS3DEV=/usr/local/ps3dev
export PSL1GHT=$PS3DEV/psl1ght
export PATH=$PATH:$PS3DEV/bin:$PSL1GHT/bin

# Create and own them (avoid sudo installs into root-owned dirs)
sudo mkdir -p "$PS3DEV" "$PSL1GHT"
sudo chown -R "$USER":"$USER" "$PS3DEV"

# Make permanent (add to ~/.bashrc)
echo 'export PS3DEV=/usr/local/ps3dev' >> ~/.bashrc
echo 'export PSL1GHT=$PS3DEV/psl1ght' >> ~/.bashrc
echo 'export PATH=$PATH:$PS3DEV/bin:$PSL1GHT/bin' >> ~/.bashrc
source ~/.bashrc
```

## Step 4: Install PS3 Toolchain

### Clone the Toolchain Repository
```bash
# Go to your home directory (Linux filesystem - avoid Windows filesystem)
cd ~

# Clone the PS3 toolchain
git clone https://github.com/ps3dev/ps3toolchain.git
cd ps3toolchain
```

### Build the Toolchain
```bash
# Set environment variables for sudo
sudo PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin:/usr/local/ps3dev/bin:/usr/local/ps3dev/ppu/bin:/usr/local/ps3dev/spu/bin" PS3DEV=/usr/local/ps3dev PSL1GHT=/usr/local/psl1ght ./toolchain.sh 1 2 3 4
```

### Build Options
- **FAST COMPILE COMMAND**: `export MAKE="make -j$(nproc --all)"`
- **PPU Toolchain only**: `./toolchain.sh 1 2 3 4`
- **SPU Toolchain only**: `./toolchain.sh 5 6 7`
- **Full toolchain**: `./toolchain.sh` (all steps)

## Step 5: Verify Installation

Check that the toolchain is properly installed:

```bash
# Check if tools are available
powerpc64-ps3-elf-gcc --version
spu-gcc --version

# Check environment variables
echo "PS3DEV: $PS3DEV"
echo "PSL1GHT: $PSL1GHT"
```

## Step 6: Build Your PS3 Plugin

Once the toolchain is installed, you can build your PS3 plugin:

```bash
# Go to your plugin source directory
cd ~/pluginps3

# Clean any previous builds
make clean

# Build the plugin (single-threaded for compatibility)
make -j1

# Or build with parallel compilation (faster)
export MAKE="make -j$(nproc --all)"
make
```

### Build Targets
- `make` - Build release version
- `make clean` - Clean build artifacts
- `make -j1` - Single-threaded build (recommended for first build)
- `make -j$(nproc --all)` - Parallel build using all CPU cores

### Build Artifacts
After successful compilation, you'll get:
- `guitar_remap.sprx` - The main plugin file
- Other build artifacts in the project directory

## Alternative: Using Git Bash (if WSL fails)

If WSL installation continues to fail, you can use Git Bash:

1. **Install MSYS2** for Unix-like tools
2. **Install build tools** via pacman
3. **Follow similar steps** but adapt for Windows environment

## Common Issues and Solutions

### Permission Errors
```bash
sudo chown -R $USER:$USER /usr/local/ps3dev
sudo chown -R $USER:$USER /usr/local/psl1ght
```

### Environment Variable Issues
```bash
# Use sudo -E to preserve environment
sudo -E ./toolchain.sh

# Or set variables explicitly
sudo PATH="..." PS3DEV=... PSL1GHT=... ./toolchain.sh
```

### Filesystem Issues
- **Avoid Windows filesystem** (`/mnt/f/`) for builds
- **Use Linux filesystem** (`~`) for better performance
- **Fix permissions** if working on Windows filesystem

## Next Steps

Once the toolchain is installed, you can:
1. **Compile PS3 applications** using the cross-compilers
2. **Link against PSL1GHT libraries** for PS3-specific functionality
3. **Build your PS3 plugin** using the installed tools

## Resources

- [PS3 Toolchain Repository](https://github.com/ps3dev/ps3toolchain)
- [PSL1GHT SDK](https://github.com/ps3dev/psl1ght)
- [WSL Documentation](https://docs.microsoft.com/en-us/windows/wsl/) 