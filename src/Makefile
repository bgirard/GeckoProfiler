OS = $(shell uname -s)
INCLUDES = -Iinclude
DEFINES = -DSPS_STANDALONE -DMOZ_ENABLE_PROFILER_SPS -DXP_MACOSX
CXXFLAGS_COMMON=$(INCLUDES) -g -Wall -Wextra -O2 -std=c++11 $(DEFINES)
CXXFLAGS = $(CXXFLAGS_COMMON)
LDFLAGS = -lstdc++ -shared
TARGET_LIB = GeckoProfiler.so

SOURCES = \
  ProfileEntry.cpp \
  ProfileJSONWriter.cpp \
  ProfilerBacktrace.cpp \
  ProfilerMarkers.cpp \
  SyncProfile.cpp \
  TableTicker.cpp \
  platform-macos.cpp \
  platform.cpp \
  shared-libraries-macos.cpp \
  include/mozilla/JSONWriter.cpp \
  include/mozilla/TimeStamp.cpp \
  include/mozilla/TimeStamp_darwin.cpp \
  include/mozilla/double-conversion/double-conversion.cpp \
  include/mozilla/double-conversion/bignum.cpp \
  include/mozilla/double-conversion/bignum-dtoa.cpp \
  include/mozilla/double-conversion/cached-powers.cpp \
  include/mozilla/double-conversion/diy-fp.cpp \
  include/mozilla/double-conversion/fixed-dtoa.cpp \
  include/mozilla/double-conversion/fast-dtoa.cpp \
  include/mozilla/double-conversion/strtod.cpp \
  $(NULL)

OBJS = ${SOURCES:.cpp=.o}

all: GeckoProfiler.so

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

#GeckoProfiler.so: $(OBJECTS)
#	echo build
