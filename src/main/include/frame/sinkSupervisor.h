#pragma once

#include "frame/frameSink.h"
#include "frame/frameSource.h"

#include <atomic>
#include <mutex>
#include <thread>

class SinkSupervisor {
public:
  SinkSupervisor(FrameSource *source, FrameSink *sink, float fpsLimit);

  SinkSupervisor(FrameSource *source, FrameSink *sink);

  ~SinkSupervisor();

private:
  std::mutex frameBufferAccess;
  std::atomic<Frame *> frameBuffer;

  FrameSource *source;
  FrameSink *sink;

  void loop();

  void newFrameCallback(Frame *frame);

  void fpsCallback();

  std::thread mainThread;

  std::atomic_bool runLoop;

  std::chrono::steady_clock::time_point highestFrameTimestamp;
};