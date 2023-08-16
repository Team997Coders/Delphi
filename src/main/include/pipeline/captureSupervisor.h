#pragma once

#include "pipeline/frameSource.h"

#include <functional>
#include <thread>

class CaptureSupervisor {
public:
  CaptureSupervisor(FrameSource *source, std::function<void(Frame *)> newFrameCallback, float fpsLimit);

  CaptureSupervisor(FrameSource *source, std::function<void(Frame *)> newFrameCallback);

private:
  FrameSource *source;

  std::function<void(Frame *)> frameCallback;

  void newFrameCallback(Frame *frame);

  void fpsCallback();

  std::chrono::steady_clock::time_point highestFrameTimestamp;
};