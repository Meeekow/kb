#!/bin/bash

# Launch qmk getting started webpage
# firefox --private-window https://github.com/qmk/qmk_firmware/blob/master/docs/newbs_getting_started.md

# Install prerequisite
sudo pacman --needed --noconfirm -S git python-pip libffi

# Make sure pwd is /home dir
cd $HOME

# Clone qmk repo along with the submodules
git clone --recurse-submodules --depth=1 https://github.com/qmk/qmk_firmware

# Symlink my files
cd ~/qmk_firmware/keyboards/ferris/keymaps/default
rm -rf *
ln -s ~/kb/keyboards/ferris/keymaps/default/* .

# Symlink my files
cd ~/qmk_firmware/keyboards/ferris/sweep
rm -rf rules.mk
ln -s ~/kb/keyboards/ferris/sweep/rules.mk .

# Go to qmk directory and run pip install for qmk
cd $HOME/qmk_firmware/ && sudo python3 -m pip install --user qmk

