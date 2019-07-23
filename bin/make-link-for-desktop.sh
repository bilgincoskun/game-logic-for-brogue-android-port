#!/usr/bin/env bash
cd `dirname $0`
export PATH=`pwd`
echo "\
[Desktop Entry]
Version=1.7.5
Type=Application
Name=Brogue
GenericName=Roguelike
Comment=Brave the Dungeons of Doom!
Exec=${PATH}/brogue
Path=${PATH}
Icon=${PATH}/brogue-icon.png
Terminal=false" > brogue.desktop

chmod +x brogue.desktop

echo "Created brogue.desktop."
echo "If your desktop is in the default location, type:"
echo "mv brogue.desktop ~/Desktop"

