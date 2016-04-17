#!/bin/bash
#
echo "Usage: . ./define_variable.sh"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/lib
export PTERMINAL=$(pwd)/commands
