#pragma once

#include "frame/frameSource.h"
#include "processing/processingSink.h"

#include <mutex>
#include <thread>

class ProcessingSupervisor {
public:
  ProcessingSupervisor(FrameSource *source, ProcessingSink *sink, float fpsLimit);

  ~ProcessingSupervisor();

private:
  std::mutex frameBufferAccess;
  Frame *frameBuffer;

  FrameSource *source;
  ProcessingSink *sink;

  void loop();

  void newFrameCallback(Frame *frame);

  void fpsCallback();

  std::thread mainThread;

  volatile bool runLoop;

  std::chrono::steady_clock::time_point highestFrameTimestamp;
};