#!/bin/bash

set -e

git submodule update --init --recursive
./gyp/gyp build.gyp --depth=. -f ninja
ninja -C out/Default
