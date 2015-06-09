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

  profiler_start(100000, 10, nullptr, 0, nullptr, 0);

  atexit(shutdown);
}

