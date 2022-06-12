#!/bin/bash

echo "Builds the dockcross image"
docker build -t tbstudio-fedora -f Dockerfile.fedora .
docker build -t tbstudio-windows -f Dockerfile.windows .
echo "Run"
docker run -it tbstudio-fedora bash
docker run -it tbstudio-windows cmd.exe

