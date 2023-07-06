#pragma once

#include "opencv2/videoio.hpp"

#include "frame/frame.h"

#include <functional>
#include <thread>
#include <vector>

class FrameSource {
public:
  FrameSource(int cameraIndex);

  ~FrameSource();

  Frame getCurrentFrame();

  void registerCallbackOnNewFrame(void (*cb)(Frame frame));

  float getFPS();

  void setFPSMovingAverageGain(float gain);

private:
  cv::VideoCapture capture;

  std::thread frameWatcher;

  void frameWatcherFunction();

  volatile bool runFramewatcherLoop;

  std::vector<std::function<void(Frame)>> callbacks;

  std::chrono::steady_clock::time_point lastFrameTimestamp;

  float fps;

  float fpsMovingAverageGain;
};