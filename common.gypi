{
    'defines': [
      'SPS_STANDALONE',
      'MOZ_ENABLE_PROFILER_SPS',
    ],
    'include_dirs': [
      'src',
      'third_party/mfbt/include',
      'third_party/spidermonkey/include',
    ],
    'cflags': [
      '-std=c++11',
      '-g',
      '-O0',
    ],
    'xcode_settings': {
      'OTHER_CFLAGS': [
        '-std=c++11',
        '-g',
        '-O0',
      ],
    },
    'conditions': [
      ['OS=="mac"', {
        'defines': [
          'XP_MACOSX',
        ],
      }],
      ['OS=="linux"', {
        'defines': [
          'XP_LINUX',
          'PRId64=l64d'
        ],
      }],
    ],
}
