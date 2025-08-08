#!/bin/bash

# PS3 HEN Guitar Controller Remapping Plugin Installation Script

echo "=========================================="
echo "PS3 HEN Guitar Controller Remapping Plugin"
echo "=========================================="
echo ""

# Check if running on PS3
if [ ! -d "/dev_hdd0" ]; then
    echo "Error: This script must be run on a PS3 with HEN installed."
    echo "Please copy the files manually to your PS3's /dev_hdd0/plugins/ directory."
    exit 1
fi

# Create plugins directory if it doesn't exist
if [ ! -d "/dev_hdd0/plugins" ]; then
    echo "Creating plugins directory..."
    mkdir -p /dev_hdd0/plugins
fi

# Copy plugin files
echo "Installing plugin files..."

# Copy the compiled plugin
if [ -f "guitar_remap.sprx" ]; then
    cp guitar_remap.sprx /dev_hdd0/plugins/
    echo "✓ Copied guitar_remap.sprx"
else
    echo "⚠ Warning: guitar_remap.sprx not found. Please compile the plugin first."
fi

# Copy configuration file
if [ -f "guitar_remap.conf" ]; then
    cp guitar_remap.conf /dev_hdd0/plugins/
    echo "✓ Copied guitar_remap.conf"
else
    echo "⚠ Warning: guitar_remap.conf not found."
fi

# Set permissions
echo "Setting file permissions..."
chmod 644 /dev_hdd0/plugins/guitar_remap.sprx 2>/dev/null
chmod 644 /dev_hdd0/plugins/guitar_remap.conf 2>/dev/null

echo ""
echo "Installation complete!"
echo ""
echo "Next steps:"
echo "1. Restart your PS3 or reload HEN"
echo "2. Connect your generic guitar controller"
echo "3. The plugin will automatically detect and remap your controller"
echo ""
echo "To customize button mappings, edit:"
echo "  /dev_hdd0/plugins/guitar_remap.conf"
echo ""
echo "For help, see the README.md file." 