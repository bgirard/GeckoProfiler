#include "GeckoProfiler.h"

#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

#ifdef XP_MACOSX
struct interpose {
  void *new_func;
  void *orig_func;
};
#endif

#ifdef XP_MACOSX
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

  if (profile.get()) {
    if (std::getenv("MOZ_PROFILER_OUT_DIR")) {
      std::stringstream s;
      s << std::getenv("MOZ_PROFILER_OUT_DIR");
      s << "/profile_";;
      s << getpid();
      s << ".profile";
      std::string fileName = s.str();

      std::ofstream stream;
      stream.open(fileName.c_str());
      if (stream.is_open()) {
        stream << profile.get();
        stream.close();
      } else {
        printf("Can't save %s\n", fileName.c_str());
      }
    } else {
      printf("profile:\n%s\n", profile.get());
    }
  } else {
    printf("no profile\n");
  }

  profiler_shutdown();
}

static void shutdownSignal(int signo, siginfo_t *si, void *context) {
  shutdown();
}

__attribute__((constructor)) static void standalone_init() {
  int a;
  profiler_init(&a);

  int profileSize = 100000;
  int profileInterval = 1;
  const char* features[] = {"stackwalk", "threads"};
  profiler_start(profileSize, profileInterval, features, MOZ_ARRAY_LENGTH(features), nullptr, 0);

}

#ifdef XP_MACOSX
// Some applications skip atexit, exit. _exit() is more reliable
void _exit_my(int status) {
  shutdown();
  _exit(status);
}

static const struct interpose interposerExit[] __attribute__ ((section("__DATA, __interpose"))) __attribute__((used)) = {
  {(void*)_exit_my, (void*)_exit}
};
#else

#endif
