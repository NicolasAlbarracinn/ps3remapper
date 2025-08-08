#!/bin/bash

# PS3 HEN Guitar Controller Remapping Plugin - Automated Build & Install Script

set -e  # Exit on any error

echo "=========================================="
echo "PS3 HEN Guitar Controller Remapping Plugin"
echo "Automated Build & Installation Script"
echo "=========================================="
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if we're on a supported system
check_system() {
    print_status "Checking system requirements..."
    
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        print_success "Linux system detected"
    elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
        print_warning "Windows detected - please use WSL for best results"
    else
        print_error "Unsupported operating system: $OSTYPE"
        exit 1
    fi
}

# Check if PS3 SDK is installed
check_ps3_sdk() {
    print_status "Checking PS3 SDK installation..."
    
    if command -v ppu-gcc &> /dev/null; then
        print_success "PS3 SDK (ppu-gcc) found"
        ppu-gcc --version | head -1
    else
        print_error "PS3 SDK not found. Please install PSL1GHT first."
        echo ""
        echo "To install PSL1GHT:"
        echo "1. git clone https://github.com/ps3dev/PSL1GHT.git"
        echo "2. cd PSL1GHT"
        echo "3. make"
        echo "4. sudo make install"
        echo "5. Add to PATH: export PATH=\$PATH:/usr/local/ps3dev/host/ppu/bin"
        exit 1
    fi
}

# Build the plugin
build_plugin() {
    print_status "Building plugin..."
    
    # Clean previous builds
    if [ -f "Makefile" ]; then
        make clean > /dev/null 2>&1 || true
    fi
    
    # Build the plugin
    if make; then
        print_success "Plugin built successfully!"
        
        if [ -f "guitar_remap.sprx" ]; then
            print_success "Plugin file created: guitar_remap.sprx"
            ls -lh guitar_remap.sprx
        else
            print_error "Plugin file not found after build"
            exit 1
        fi
    else
        print_error "Build failed!"
        exit 1
    fi
}

# Prepare installation files
prepare_installation() {
    print_status "Preparing installation files..."
    
    # Create installation directory
    mkdir -p ps3_installation
    
    # Copy required files
    cp guitar_remap.sprx ps3_installation/ 2>/dev/null || print_error "Plugin file not found"
    cp guitar_remap.conf ps3_installation/ 2>/dev/null || print_warning "Config file not found"
    cp install.sh ps3_installation/ 2>/dev/null || print_warning "Install script not found"
    cp find_ps3_ip.sh ps3_installation/ 2>/dev/null || print_warning "IP finder script not found"
    cp README.md ps3_installation/ 2>/dev/null || print_warning "README not found"
    
    # Make scripts executable
    chmod +x ps3_installation/*.sh 2>/dev/null || true
    
    print_success "Installation files prepared in ps3_installation/ directory"
    ls -la ps3_installation/
}

# Check if PS3 is accessible
check_ps3_access() {
    print_status "Checking PS3 accessibility..."
    
    if [ -d "/dev_hdd0" ]; then
        print_success "PS3 filesystem detected - running on PS3"
        return 0
    else
        print_warning "PS3 filesystem not detected - running on development machine"
        return 1
    fi
}

# Install on PS3
install_on_ps3() {
    print_status "Installing plugin on PS3..."
    
    if [ -f "install.sh" ]; then
        chmod +x install.sh
        if ./install.sh; then
            print_success "Plugin installed successfully!"
        else
            print_error "Installation failed!"
            exit 1
        fi
    else
        print_error "Install script not found"
        exit 1
    fi
}

# Show installation instructions
show_instructions() {
    print_status "Installation files ready!"
    echo ""
    echo "To install on your PS3:"
    echo ""
    echo "Method 1 - USB Transfer (Recommended):"
    echo "1. Format a USB drive as FAT32"
    echo "2. Copy the ps3_installation/ folder to USB"
    echo "3. Insert USB into PS3"
    echo "4. Copy files to /dev_hdd0/plugins/"
    echo "5. Restart PS3 and load HEN"
    echo ""
    echo "Method 2 - Network Transfer:"
    echo "1. Enable FTP on PS3 (if available)"
    echo "2. Upload files via FTP to /dev_hdd0/plugins/"
    echo "3. Restart PS3 and load HEN"
    echo ""
    echo "Method 3 - Direct Installation:"
    echo "1. Connect to PS3 via SSH/terminal"
    echo "2. Run: ./install.sh"
    echo "3. Restart PS3 and load HEN"
    echo ""
    echo "After installation:"
    echo "1. Connect your guitar controller"
    echo "2. Access web interface at: http://your-ps3-ip:8080"
    echo "3. Test button mappings"
    echo ""
    echo "Files created:"
    ls -la ps3_installation/
}

# Main execution
main() {
    echo "Starting automated build and installation process..."
    echo ""
    
    # Check system
    check_system
    
    # Check PS3 SDK
    check_ps3_sdk
    
    # Build plugin
    build_plugin
    
    # Prepare installation
    prepare_installation
    
    # Check if we're on PS3
    if check_ps3_access; then
        # We're on PS3, install directly
        install_on_ps3
        print_success "Plugin installed and ready to use!"
        echo ""
        echo "Next steps:"
        echo "1. Restart PS3 or reload HEN"
        echo "2. Connect your guitar controller"
        echo "3. Access web interface at: http://your-ps3-ip:8080"
    else
        # We're on development machine, show instructions
        show_instructions
    fi
    
    echo ""
    print_success "Build and installation process completed!"
}

# Run main function
main "$@" 