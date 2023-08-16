#pragma once

#include "pipeline/frame.h"

#include <atomic>
#include <functional>
#include <string>
#include <thread>
#include <vector>

class FrameSource {
public:
  FrameSource();

  ~FrameSource();

  virtual Frame* getCurrentFrame() = 0;

  virtual std::string getUniqueName() = 0;

  void registerCallbackOnNewFrame(std::function<void(Frame *)>);

  float getFPS();

  void setFPSMovingAverageGain(float gain);

private:
  std::thread frameWatcher;

  void frameWatcherFunction();

  std::atomic_bool runFramewatcherLoop;

  std::vector<std::function<void(Frame *)>> callbacks;

  std::chrono::steady_clock::time_point lastFrameTimestamp;

  std::atomic<float> fps;

  std::atomic<float> fpsMovingAverageGain;
};