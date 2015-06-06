#include "GeckoProfiler.h"

#include <chrono>
#include <thread>

void longSleep() {
  PROFILER_LABEL("Sampe", "twoSecondSleep", js::ProfileEntry::Category::OTHER);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void tinySleep() {
  PROFILER_LABEL("Sampe", "tinySleep", js::ProfileEntry::Category::OTHER);
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

int main() {
  int a;
  profiler_init(&a);

  PROFILER_LABEL("Sample", "Main", js::ProfileEntry::Category::OTHER);
  PROFILER_LABEL("Sample", "SomeFunc", js::ProfileEntry::Category::OTHER);
  PROFILER_LABEL("Sample", "ExampleDispatcher", js::ProfileEntry::Category::OTHER);

  profiler_start(100000, 10, nullptr, 0, nullptr, 0);

  {
    PROFILER_LABEL("Sample", "BeforeLongSleep", js::ProfileEntry::Category::OTHER);
    longSleep();
  }

  tinySleep();

  PROFILER_LABEL("Sample", "After", js::ProfileEntry::Category::OTHER);

  auto profile = profiler_get_profile();

  printf("%s", profile.get());

  profiler_shutdown();

  return 0;
}
