#include "frame/sinkSupervisor.h"
#include "util/timedCallbackProvider.h"

SinkSupervisor::SinkSupervisor(FrameSource *source, FrameSink *sink, float fpsLimit) {
  this->source = source;
  this->sink = sink;

  runLoop = true;
  mainThread = std::thread{&SinkSupervisor::loop, this};

  frameBuffer = nullptr;

  highestFrameTimestamp = std::chrono::steady_clock::time_point::min();

  if (fpsLimit > 0) {
    TimedCallbackProvider cb = TimedCallbackProvider{std::bind(&SinkSupervisor::fpsCallback, this),
                                                     std::chrono::milliseconds{static_cast<int>(1000 / fpsLimit)}};
    cb.start();
  } else {
    source->registerCallbackOnNewFrame(std::bind(&SinkSupervisor::newFrameCallback, this, std::placeholders::_1));
  };
};

SinkSupervisor::SinkSupervisor(FrameSource *source, FrameSink *sink) { SinkSupervisor(source, sink, -1); };

SinkSupervisor::~SinkSupervisor() {
  runLoop = false;
  mainThread.join();
};

void SinkSupervisor::loop() {
  while (runLoop) {
    if (frameBuffer != nullptr) {
      frameBufferAccess.lock();
      Frame *storage = frameBuffer;
      frameBuffer = nullptr;
      frameBufferAccess.unlock();
      sink->accept(*storage);
    };
  };
};

void SinkSupervisor::newFrameCallback(Frame *frame) {
  if (frame != nullptr) {
    frameBufferAccess.lock();
    frameBuffer = frame;
    frameBufferAccess.unlock();
  };
};

void SinkSupervisor::fpsCallback() {
  Frame frame = source->getCurrentFrame();

  if (frame.captureTimestamp > highestFrameTimestamp) {
    frameBufferAccess.lock();
    highestFrameTimestamp = frame.captureTimestamp;
    frameBuffer = &frame;
    frameBufferAccess.unlock();
  };
};