#pragma once

#include "opencv2/videoio.hpp"

#include "frame/frame.h"

#include <functional>
#include <thread>
#include <vector>
#include <atomic>

class FrameSource {
public:
  FrameSource(int cameraIndex);

  ~FrameSource();

  Frame getCurrentFrame();

  void registerCallbackOnNewFrame(std::function<void(Frame *)>);

  float getFPS();

  void setFPSMovingAverageGain(float gain);

private:
  cv::VideoCapture capture;

  std::thread frameWatcher;

  void frameWatcherFunction();

  std::atomic_bool runFramewatcherLoop;

  std::vector<std::function<void(Frame *)>> callbacks;

  std::chrono::steady_clock::time_point lastFrameTimestamp;

  std::atomic<float> fps;

  std::atomic<float> fpsMovingAverageGain;
};