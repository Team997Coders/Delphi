#pragma once

#include <chrono>
#include <functional>
#include <thread>
#include <vector>

class TimedCallbackProvider {
public:
  TimedCallbackProvider(std::vector<std::function<void()>> callbacks, std::chrono::milliseconds period);

  TimedCallbackProvider(std::function<void()> callback, std::chrono::milliseconds period);

  ~TimedCallbackProvider();

  void start();

private:
  std::vector<std::function<void()>> callbacks;
  std::chrono::milliseconds period;

  std::thread thread;
  void threadEntryPoint();

  volatile bool runThread;
};