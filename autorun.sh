#!/bin/bash

# Launch qmk getting started webpage
# firefox --private-window https://github.com/qmk/qmk_firmware/blob/master/docs/newbs_getting_started.md

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

# Compile
# qmk compile -kb ferris/sweep -km default -e CONVERT_TO=promicro_rp2040

# Go to qmk directory
# cd $HOME/qmk_firmware/

# Run pip install for qmk
# python3 -m pip install --user qmk

# Hotfix for qmk not found error
# echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc

