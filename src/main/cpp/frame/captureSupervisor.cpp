#include "frame/captureSupervisor.h"
#include "util/timedCallbackProvider.h"

CaptureSupervisor::CaptureSupervisor(FrameSource *source, std::function<void(Frame *)> newFrameCallback,
                                     float fpsLimit) {
  this->source = source;
  frameCallback = newFrameCallback;

  highestFrameTimestamp = std::chrono::steady_clock::time_point::min();

  if (fpsLimit > 0) {
    TimedCallbackProvider cb = TimedCallbackProvider{std::bind(&CaptureSupervisor::fpsCallback, this),
                                                     std::chrono::milliseconds{static_cast<int>(1000 / fpsLimit)}};
    cb.start();
  } else {
    source->registerCallbackOnNewFrame(std::bind(&CaptureSupervisor::newFrameCallback, this, std::placeholders::_1));
  };
};

CaptureSupervisor::CaptureSupervisor(FrameSource *source, std::function<void(Frame *)> newFrameCallback) {
  CaptureSupervisor(source, newFrameCallback, -1);
};

void CaptureSupervisor::newFrameCallback(Frame *frame) {
  if (frame != nullptr) {
    frameCallback(frame);
  };
};

void CaptureSupervisor::fpsCallback() {
  Frame* frame = source->getCurrentFrame();

  if (frame->captureTimestamp > highestFrameTimestamp) {
    highestFrameTimestamp = frame->captureTimestamp;

    frameCallback(frame);
  };
};