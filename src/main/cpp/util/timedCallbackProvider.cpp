#include "util/timedCallbackProvider.h"

TimedCallbackProvider::TimedCallbackProvider(std::vector<std::function<void()>> callbacks,
                                             std::chrono::milliseconds period) {
  this->callbacks = callbacks;
  this->period = period;
};

TimedCallbackProvider::TimedCallbackProvider(std::function<void()> callback, std::chrono::milliseconds period) {
  std::vector<std::function<void()>> vector{};
  vector.push_back(callback);
  this->callbacks = vector;
  this->period = period;
};

TimedCallbackProvider::~TimedCallbackProvider() {
  runThread = false;
  thread.join();
};

void TimedCallbackProvider::start() {
  runThread = true;
  thread = std::thread(&TimedCallbackProvider::threadEntryPoint, this);
};

void TimedCallbackProvider::threadEntryPoint() {
  while (runThread) {
    for (std::function<void()> cb : callbacks) {
      if (cb != nullptr)
        cb();
    };

    std::this_thread::sleep_for(period);
  };
};