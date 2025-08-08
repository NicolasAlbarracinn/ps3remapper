#!/bin/bash

# PS3 IP Address Finder for Guitar Controller Remapping Plugin

echo "=========================================="
echo "PS3 IP Address Finder"
echo "=========================================="
echo ""

echo "To find your PS3's IP address, follow these steps:"
echo ""
echo "1. On your PS3, go to:"
echo "   Settings → Network Settings → Internet Connection Status"
echo ""
echo "2. Look for the IP address displayed (usually something like 192.168.1.xxx)"
echo ""
echo "3. Once you have the IP address, access the interface:"
echo ""

# Check if we can detect the PS3 on the network
echo "Attempting to detect PS3 on local network..."
echo ""

# Try common PS3 IP ranges
for i in {1..254}; do
    # Try common home network ranges
    for base in "192.168.1" "192.168.0" "10.0.0" "172.16.0"; do
        ip="$base.$i"
        if ping -c 1 -W 1 "$ip" >/dev/null 2>&1; then
            echo "Found device at $ip"
            # Try to connect to webMAN MOD first
            if curl -s --connect-timeout 2 "http://$ip/" >/dev/null 2>&1; then
                echo "🎉 Found PS3 with webMAN MOD at: http://$ip/"
                echo "   Guitar controller plugin interface: http://$ip/guitar_remap"
                echo ""
                echo "   This is likely your PS3 running webMAN MOD!"
                echo "   The guitar controller plugin will integrate with webMAN MOD."
                echo ""
                exit 0
            # Try standalone plugin interface
            elif curl -s --connect-timeout 2 "http://$ip:8080/guitar_remap" >/dev/null 2>&1; then
                echo "🎉 Found PS3 with standalone plugin at: http://$ip:8080/guitar_remap"
                echo "   This is likely your PS3 running the guitar controller plugin!"
                echo ""
                exit 0
            fi
        fi
    done
done

echo "Could not automatically detect PS3 with web interface."
echo "Please manually check your PS3's IP address as described above."
echo ""
echo "Access URLs:"
echo "1. With webMAN MOD: http://your-ps3-ip/guitar_remap"
echo "2. Standalone mode: http://your-ps3-ip:8080/guitar_remap"
echo ""
echo "Alternative methods to find your PS3 IP:"
echo "1. Check your router's admin panel for connected devices"
echo "2. Use a network scanner app on your phone"
echo "3. Check your PS3's network settings"
echo ""
echo "Make sure:"
echo "- Your PS3 is connected to the same network as your computer"
echo "- The guitar controller plugin is installed and running"
echo "- webMAN MOD is running (for integrated mode)"
echo "- Port 8080 is not blocked by your firewall (for standalone mode)" 