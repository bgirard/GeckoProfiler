#include "GeckoProfiler.h"

#include <chrono>
#include <thread>

int main() {
  int a;
  profiler_init(&a);

  PROFILER_LABEL("Sample", "Main", js::ProfileEntry::Category::OTHER);

  profiler_start(10000, 1, nullptr, 0, nullptr, 0);

  std::this_thread::sleep_for(std::chrono::seconds(2));

  auto profile = profiler_get_profile();

  printf("%s", profile.get());

  profiler_shutdown();

  return 0;
}
