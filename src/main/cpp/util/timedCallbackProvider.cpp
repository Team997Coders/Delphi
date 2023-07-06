#include "util/timedCallbackProvider.h"

TimedCallbackProvider::TimedCallbackProvider(std::vector<std::function<void()>> callbacks,
                                             std::chrono::milliseconds period) {
  this->callbacks = callbacks;
  this->period = period;

  runThread = true;
  thread = std::thread(&TimedCallbackProvider::threadEntryPoint, this);
};

TimedCallbackProvider::~TimedCallbackProvider() {
  runThread = false;
  thread.join();
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