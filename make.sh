#!/bin/bash

# You shouldn't be building this here, you should be building this stuff as
#  part of your project, so this is just an example shell script and not a
#  formal makefile or whatever.

if [ ! -d "sdk" ]; then
    echo "This script expects the Steamworks SDK to be unpacked here." 1>&2
    echo "When unzipped, it makes an 'sdk' directory. Put that here." 1>&2
    exit 1
fi

set -e
set -x

OSTYPE=`uname -s`
if [ "$OSTYPE" = "Linux" ]; then
    g++ -o steamshim -Wall -O0 -ggdb3 steamshim_parent.cpp -I sdk/public sdk/redistributable_bin/linux64/libsteam_api.so
    gcc -o testapp -Wall -O0 -ggdb3 testapp.c steamshim_child.c
elif [ "$OSTYPE" = "Darwin" ]; then
    clang++ -o steamshim -Wall -O0 -ggdb3 steamshim_parent.cpp -I sdk/public sdk/redistributable_bin/osx32/libsteam_api.dylib
    clang -o testapp -Wall -O0 -ggdb3 testapp.c steamshim_child.c
else
    echo "write me" 1>&2
    exit 1
fi

exit 0

