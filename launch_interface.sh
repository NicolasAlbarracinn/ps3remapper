#!/bin/bash

# PS3 HEN Guitar Controller Remapping Plugin Interface Launcher

echo "=========================================="
echo "PS3 HEN Guitar Controller Remapping Plugin"
echo "=========================================="
echo ""

# Check if running on PS3
if [ ! -d "/dev_hdd0" ]; then
    echo "Error: This script must be run on a PS3 with HEN installed."
    echo "Please run this on your PS3 console."
    exit 1
fi

# Check if plugin is installed
if [ ! -f "/dev_hdd0/plugins/guitar_remap.sprx" ]; then
    echo "Error: Plugin not found at /dev_hdd0/plugins/guitar_remap.sprx"
    echo "Please install the plugin first using install.sh"
    exit 1
fi

echo "Launching Guitar Controller Remapping Interface..."
echo ""
echo "This interface will show you:"
echo "- All connected controllers"
echo "- Real-time button press detection"
echo "- How your guitar controller inputs are recognized"
echo "- Current button mappings"
echo ""
echo "Controls:"
echo "- Press any button to see input detection"
echo "- Press START to exit interface"
echo "- Press SELECT to refresh"
echo ""
echo "Press any key to continue..."

# Wait for user input
read -n 1 -s

# Launch the interface
# Note: This would typically be done through a homebrew application
# For now, we'll show instructions on how to access it

echo ""
echo "To access the interface:"
echo "1. Make sure the plugin is loaded (restart PS3 or reload HEN)"
echo "2. The interface will automatically start when the plugin loads"
echo "3. You can see the interface output in the system logs"
echo ""
echo "Alternative access methods:"
echo "- Use a homebrew application that can display console output"
echo "- Check the PS3 system logs for plugin output"
echo "- Use a network-based interface (if implemented)"
echo ""
echo "For troubleshooting, check:"
echo "- /dev_hdd0/plugins/guitar_remap.conf (configuration)"
echo "- System logs for plugin messages"
echo "- Controller connection status" 