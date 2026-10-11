#!/usr/bin/env bash
set -euo pipefail

# Run manually: bash setup_ubuntu.sh
# Intended for Ubuntu or Debian with sudo access.
sudo apt-get update
sudo apt-get install -y build-essential cmake ninja-build gdb git pkg-config curl ca-certificates openssh-client clang-format unzip

g++ --version
cmake --version
ninja --version
gdb --version
git --version
