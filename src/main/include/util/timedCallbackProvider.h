#pragma once

#include <chrono>
#include <functional>
#include <thread>
#include <vector>

class TimedCallbackProvider {
public:
  TimedCallbackProvider(std::vector<std::function<void()>> callbacks, std::chrono::milliseconds period);

  ~TimedCallbackProvider();

private:
  std::vector<std::function<void()>> callbacks;
  std::chrono::milliseconds period;

  std::thread thread;
  void threadEntryPoint();

  volatile bool runThread;
};