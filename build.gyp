  {
    'targets': [
      {
        'target_name': 'GeckoProfiler',
        'type': '<(library)',
        'includes': [
          'common.gypi'
        ],
        'dependencies': [
        ],
        'sources': [
          'src/ProfileEntry.cpp',
          'src/ProfileJSONWriter.cpp',
          'src/ProfilerBacktrace.cpp',
          'src/ProfilerMarkers.cpp',
          'src/SyncProfile.cpp',
          'src/TableTicker.cpp',
          'src/platform.cpp',
          'third_party/mfbt/double-conversion/bignum.cc',
          'third_party/mfbt/double-conversion/bignum-dtoa.cc',
          'third_party/mfbt/double-conversion/cached-powers.cc',
          'third_party/mfbt/double-conversion/double-conversion.cc',
          'third_party/mfbt/double-conversion/diy-fp.cc',
          'third_party/mfbt/double-conversion/fixed-dtoa.cc',
          'third_party/mfbt/double-conversion/fast-dtoa.cc',
          'third_party/mfbt/double-conversion/strtod.cc',
          'third_party/mfbt/JSONWriter.cpp',
          'third_party/mfbt/TimeStamp.cpp',
        ],
        'conditions': [
          ['OS=="mac"', {
            'sources': [
              'src/platform-macos.cc',
              'src/shared-libraries-macos.cc',
              'third_party/mfbt/TimeStamp_darwin.cpp',
            ]
          }],
          ['OS=="linux"', {
            'sources': [
              'src/platform-linux.cc',
              'src/shared-libraries-linux.cc',
              'third_party/mfbt/TimeStamp_posix.cpp',
            ],
            'link_settings': {
              'libraries': [
                '-lpthread',
              ]
            }
          }],
        ],
      },{
        'target_name': 'hello_world',
        'type': 'executable',
        'dependencies': [
          'GeckoProfiler'
        ],
        'includes': [
          'common.gypi'
        ],
        'sources': [
          'samples/hello_world.cpp',
        ],
      }
    ],
  }
