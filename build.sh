#!/bin/bash

set -e

./gyp/gyp build.gyp -Dlibrary=shared_library --depth=. -f ninja
ninja -C out/Default
