#!/bin/bash
echo "export PATH=$PATH:~/.platformio/penv/bin"
export PATH=$PATH:~/.platformio/penv/bin

echo "copy 'pio' to /usr/local/bin/. requires superuser"
sudo cp ~/.platformio/penv/bin/pio /usr/local/bin/

echo "checking pio version"
pio --version
