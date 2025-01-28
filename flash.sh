#!/bin/bash

XFEL_PATH=/Users/climatex/Documents/Coding-Zone/Self_Projects/xfel

make clean && make -j
$XFEL_PATH/xfel ddr d1 && $XFEL_PATH/xfel write 0x40000000 army-ant.bin && $XFEL_PATH/xfel exec 0x40000000