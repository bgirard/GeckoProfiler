#!/bin/bash

set -e

./gyp/gyp build.gyp -Dlibrary=static_library --depth=. -f ninja
ninja -C out/Default
