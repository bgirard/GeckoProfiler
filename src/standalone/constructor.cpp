#include "GeckoProfiler.h"

#include <stdlib.h>

static void shutdown() {
  auto profile = profiler_get_profile();

  printf("profile:\n%s\n", profile.get());

  profiler_shutdown();
}

__attribute__((constructor)) static void standalone_init() {
  int a;
  profiler_init(&a);

  int profileSize = 100000;
  int profileInterval = 10;
  const char* features[] = {"stackwalk"};
  profiler_start(profileSize, profileInterval, features, MOZ_ARRAY_LENGTH(features), nullptr, 0);

  atexit(shutdown);
}

