#include "GeckoProfiler.h"

void longCalc() {
  PROFILER_LABEL("Sampe", "longCalc", js::ProfileEntry::Category::OTHER);
  for (int i = 0; i < 1000000000; i++) {}
}

void tinyCalc() {
  PROFILER_LABEL("Sampe", "tinyCalc", js::ProfileEntry::Category::OTHER);
  for (int i = 0; i < 100000000; i++) {}
}

int main() {
  int a;
  profiler_init(&a);

  PROFILER_LABEL("Sample", "Main", js::ProfileEntry::Category::OTHER);
  PROFILER_LABEL("Sample", "SomeFunc", js::ProfileEntry::Category::OTHER);
  PROFILER_LABEL("Sample", "ExampleDispatcher", js::ProfileEntry::Category::OTHER);

  profiler_start(100000, 10, nullptr, 0, nullptr, 0);

  {
    PROFILER_LABEL("Sample", "BeforeLongCalc", js::ProfileEntry::Category::OTHER);
    longCalc();
  }

  tinyCalc();

  PROFILER_LABEL("Sample", "After", js::ProfileEntry::Category::OTHER);

  auto profile = profiler_get_profile();

  printf("%s", profile.get());

  profiler_shutdown();

  return 0;
}
