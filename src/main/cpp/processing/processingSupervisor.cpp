#include "processing/processingSupervisor.h"
#include "util/timedCallbackProvider.h"

ProcessingSupervisor::ProcessingSupervisor(FrameSource *source, ProcessingSink *sink, float fpsLimit) {
  this->source = source;
  this->sink = sink;

  runLoop = true;
  mainThread = std::thread{&ProcessingSupervisor::loop, this};

  frameBuffer = nullptr;

  highestFrameTimestamp = std::chrono::steady_clock::time_point::min();

  if (fpsLimit > 0) {
    TimedCallbackProvider cb = TimedCallbackProvider{std::bind(&ProcessingSupervisor::fpsCallback, this),
                                                     std::chrono::milliseconds{static_cast<int>(1000 / fpsLimit)}};
    cb.start();
  } else {
    source->registerCallbackOnNewFrame(std::bind(&ProcessingSupervisor::newFrameCallback, this, std::placeholders::_1));
  };
};

ProcessingSupervisor::~ProcessingSupervisor() {
  runLoop = false;
  mainThread.join();
};

void ProcessingSupervisor::loop() {
  while (runLoop) {
    if (frameBuffer != nullptr) {
      frameBufferAccess.lock();
      Frame *storage = frameBuffer;
      frameBuffer = nullptr;
      frameBufferAccess.unlock();
      sink->accept(storage);
    };
  };
};

void ProcessingSupervisor::newFrameCallback(Frame *frame) {
  if (frame != nullptr) {
    frameBufferAccess.lock();
    frameBuffer = frame;
    frameBufferAccess.unlock();
  };
};

void ProcessingSupervisor::fpsCallback() {
  Frame frame = source->getCurrentFrame();

  if (frame.captureTimestamp > highestFrameTimestamp) {
    frameBufferAccess.lock();
    highestFrameTimestamp = frame.captureTimestamp;
    frameBuffer = &frame;
    frameBufferAccess.unlock();
  };
};