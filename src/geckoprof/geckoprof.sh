#/bin/bash

set -e

function usage {
  echo Usage: $0 command [args ...]
}

function mac_interpose {
  export DYLD_INSERT_LIBRARIES=/usr/local/lib/libGeckoProfiler.dylib
}

OUT_DIR=$(mktemp -d /tmp/geckoprof.XXXXXXXXXXX)

if [[ -z "$@" ]]; then
  usage
  exit 1
fi

if [[ "$OSTYPE" == "linux-gnu" ]]; then
  # TODO
  echo "Platform not supported"
  exit 1
elif [[ "$OSTYPE" == "darwin"* ]]; then
  mac_interpose
else
  echo "Platform not supported"
  exit 1
fi

export MOZ_PROFILER_STARTUP=true
export MOZ_PROFILER_INTERVAL=1
export MOZ_PROFILER_ENTRIES=500000
export MOZ_PROFILER_OUT_DIR="$OUT_DIR"
"$@"
unset DYLD_INSERT_LIBRARIES

FILES_TO_MERGE=$(echo "$OUT_DIR"/*.profile)

cat << EOF | python - | tee > ${OUT_DIR}/out.sym
import json
import re
import sys
import os

profile = None

files = '$FILES_TO_MERGE'.split()
for file in files:
  fileStr = open(file, "r").read().decode("utf-8", "replace")
  if not fileStr:
    continue
  try:
    fileData = json.loads(fileStr)
  except:
    print fileStr
    raise

  fileData['threads'][0]['name'] = os.path.basename(file)

  if profile is None:
    profile = fileData
    minStartTime = profile['meta']['startTime']
  else:
    for thread in fileData['threads']:
      delta = fileData['meta']['startTime'] - minStartTime
      idxTime = thread['samples']['schema']['time']
      for sample in thread['samples']['data']:
        sample[idxTime] += delta
      idxTime = thread['markers']['schema']['time']
      for marker in thread['markers']['data']:
          marker[idxTime] += delta
      profile['threads'].append(json.dumps(fileData));

print json.dumps(profile)
EOF

PROFILE_STR=$(cat ${OUT_DIR}/out.sym | sed 's/\\/\\\\/g; s/&(?!amp;)/\&amp;/g; s/</\&lt;/g; s/>/\&gt;/g; s/"/\&quot;/g; s/'"'"'/\&#39;/g')

cat << EOF > ./out.html
 <!DOCTYPE html>
 <html>
   <head>
     <script>
var spsProfile = "${PROFILE_STR}";

var d = document.createElement("div");
d.innerHTML = spsProfile;
window.spsProfile = d.textContent;

var url = "http://people.mozilla.org/~bgirard/cleopatra/";

function onMessage(event) {
  console.log("Got msg");
  if (event.data.type == "pong") {
    window.cleopatraReady = true;
    window.cleopatraTab.postMessage({
      type: "spsProfile",
      spsProfile: spsProfile
    }, "*");
  }
}

window.addEventListener('message', onMessage);

function pingForLoad() {
  if (window.cleopatraReady) {
    return;
  }
  setTimeout(pingForLoad, 50);
  console.log("ping");
  window.cleopatraTab.postMessage({
    type: "ping"
  }, "*");
}

function openCleopatra() {
  window.cleopatraTab = window.open(url);
  window.cleopatraTab.document.addEventListener('load', function() {
    console.log("ready");
  }, true);
  pingForLoad();
}
     </script>
   </head>
   <body onload="onload">
     Data is ready:
     <input type="button" onclick="openCleopatra()" value="Open Profile"></input>
   </body>
 </html>
EOF

echo "Saved profile to: ./out.html"
open ./out.html
