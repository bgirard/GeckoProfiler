#!/bin/bash

# This project depends on some files form the mozilla tree. This scripts
# makes it easy to perform a merge given a mozilla-central checkout.

function usage {
  echo $0 mozilla-tree
}

if [ -z "$1" ]; then
  usage
  exit 1
fi

if [ ! -d "$1/tools/profiler" ]; then
  echo "$1 is not a mozilla-central checkout."
  exit 1
fi

cp "$1/js/public/ProfilingStack.h" ./third_party/spidermonkey/include/js
cp -r "$1/mfbt/" ./third_party/mfbt
cp -r "$1/tools/profiler/" ./src


# Setup the include. This should be done by the build system ideally
cp ./third_party/mfbt/*.h ./third_party/mfbt/include/mozilla
