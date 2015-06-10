#!/bin/bash

set -e

# Make sure we're up to date
./build.sh

sudo cp out/Default/libGeckoProfiler.dylib /usr/local/lib
sudo cp src/geckoprof/geckoprof.sh /usr/bin/geckoprof
