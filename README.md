[![Build Status](https://travis-ci.org/bgirard/GeckoProfiler.svg)](https://travis-ci.org/bgirard/GeckoProfiler)
![Gecko Profiler Screenshot](/images/screenshot.png?raw=true)

Gecko Profiler
=========

The Gecko Profiler is the backend of the profiler used by Firefox. It uses a unique sampling and instrumenting hybrid approach to achieve low overhead while still allowing the application to interact with the profiler. The Gecko Profiler is a built-in profiler that must be linked with your application. It provides a API for your application to interact with the profiler that is useful for providing additional context in profiles.

The Gecko Profiler is designed to track responsiveness. It provides a timeline that can be useful for identifying areas of the code that are blocking the event loop or operations that are out of budget.

Labels
======
Labels give for the application to tag the sample additional information about what the current stack frame is doing. For instance if a function is loading a file it may provide the filename. This gives the user much more control than typical sampling profiler that only record the c++ frame names.

Markers
======
Markers give the application a way to signal that something interesting occured during the timeline regardless of the state of the sampling. It can be useful to note when you startup has completed or the time boundaries of your frames for games.

GUI
======
Data is exported using a JSON format. It can be analyzed using:
http://people.mozilla.org/~bgirard/cleopatra/

For more details see: https://github.com/bgirard/cleopatra

Running
=======
1) Run ./build.sh
2) Run ./out/Default/hello_world
3) Copy the JSON profile from stdout to: http://people.mozilla.org/~bgirard/cleopatra/

Contributing
============
Github pull requests accepted
