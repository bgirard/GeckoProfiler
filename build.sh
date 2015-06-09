#!/bin/bash

set -e

./gyp/gyp build.gyp --depth=. -f ninja
ninja -C out/Default
