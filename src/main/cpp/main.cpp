#include <iostream>
#include <stdio.h>

#include "util/timedCallbackProvider.h"

using namespace std::chrono;

steady_clock::time_point lastMark = steady_clock::now();

void test() {
  steady_clock::time_point now = steady_clock::now();
  steady_clock::duration diff = now - lastMark;
  std::cout << duration_cast<microseconds>(diff).count() / 1000000.f << std::endl;
  // doing unit conversions ourselves to preserve fp precision

  lastMark = now;
};

#pragma optimize("", OFF)
void mainLoop() {
  while (true) {
    // this is needed to keep threads running, regardless of whether it contains any code
  };
};
#pragma optimize("", ON)

int main() {
  std::vector<std::function<void()>> callbacks{};
  callbacks.push_back(test);

  TimedCallbackProvider test{callbacks, milliseconds{1000}};

  mainLoop();
};