#!/bin/bash

set -e

XFEL_PATH=/mnt/d/Softwares/xfel-windows-v1.3.2/xfel-windows-v1.3.2/
XFEL=$XFEL_PATH/xfel.exe

make clean && make -j

$XFEL ddr d1

$XFEL write 0x40000000 army-ant.bin

$XFEL exec 0x40000000