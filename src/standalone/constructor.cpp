#include "GeckoProfiler.h"

#include <stdlib.h>
#include <string>

#ifdef XP_MACOSX
struct interpose {
  void *new_func;
  void *orig_func;
};


#define _GNU_SOURCE
#include <pthread.h>

int pthread_setname_np_my(const char *name) {
  int rv = pthread_setname_np(name);
  int a;
  if ((strncmp("LayoutWorker", name, strlen("LayoutWorker")) == 0 || strncmp("Paint", name, strlen("Paint")) == 0)) {
    profiler_register_thread(name, &a);
  }

  return rv;
}
static const struct interpose interposers[] __attribute__ ((section("__DATA, __interpose"))) __attribute__((used)) = {
  {(void*)pthread_setname_np_my, (void*)pthread_setname_np}
};
#endif

static void shutdown() {
  auto profile = profiler_get_profile();

  printf("profile:\n%s\n", profile.get());

  profiler_shutdown();
}

__attribute__((constructor)) static void standalone_init() {
  int a;
  profiler_init(&a);

  int profileSize = 100000;
  int profileInterval = 1;
  const char* features[] = {"stackwalk", "threads"};
  profiler_start(profileSize, profileInterval, features, MOZ_ARRAY_LENGTH(features), nullptr, 0);

  atexit(shutdown);
}

