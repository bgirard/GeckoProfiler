  {
    'targets': [
      {
        'target_name': 'GeckoProfiler',
        'type': '<(library)',
        'dependencies': [
        ],
        'defines': [
          'SPS_STANDALONE',
          'MOZ_ENABLE_PROFILER_SPS',
        ],
        'include_dirs': [
          'third_party/mfbt/include',
          'third_party/spidermonkey/include',
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
        'cflags': [
          '-std=c++11',
        ],
        'xcode_settings': {
          'OTHER_CFLAGS': [
            '-std=c++11',
          ],
        },
        'conditions': [
          ['OS=="mac"', {
            'defines': [
              'XP_MACOSX',
            ],
            'sources': [
              'src/platform-macos.cc',
              'src/shared-libraries-macos.cc',
              'third_party/mfbt/TimeStamp_darwin.cpp',
            ]
          }],
        ],
      }
    ],
  }
