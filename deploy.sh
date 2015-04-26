#!/usr/bin/env bash
#set -x

DeployLocation="bin/"

echo "Deploying resources to ${DeployLocation}"
# Asset folders
ln -srf assets/Models ${DeployLocation}
ln -srf assets/Textures ${DeployLocation}
ln -srf assets/Sounds ${DeployLocation}
# Shaders
ln -srf src/dd/Core/Shaders ${DeployLocation}
# Platform specific binaries
if [[ $# -eq 1 ]]; then
    echo "Deploying {$1} binaries to ${DeployLocation}"
    ln -srf deps/bin/$1/x64/*.dll ${DeployLocation}
fi