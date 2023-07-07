#pragma once

#include "frame/frameSource.h"
#include "processing/processingSink.h"

#include <mutex>
#include <thread>
#include <atomic>

class ProcessingSupervisor {
public:
  ProcessingSupervisor(FrameSource *source, ProcessingSink *sink, float fpsLimit);

  ~ProcessingSupervisor();

private:
  std::mutex frameBufferAccess;
  std::atomic<Frame*> frameBuffer;

  FrameSource *source;
  ProcessingSink *sink;

  void loop();

  void newFrameCallback(Frame *frame);

  void fpsCallback();

  std::thread mainThread;

  std::atomic_bool runLoop;

  std::chrono::steady_clock::time_point highestFrameTimestamp;
};