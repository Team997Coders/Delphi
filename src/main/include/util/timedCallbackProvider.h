#pragma once

#include <chrono>
#include <functional>
#include <thread>
#include <vector>
#include <atomic>

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

  std::atomic_bool runThread;
};