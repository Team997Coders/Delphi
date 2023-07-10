#include "frame/frameSource.h"

using namespace std::chrono;

FrameSource::FrameSource() {
  lastFrameTimestamp = steady_clock::now();
  fps = 0;

  setFPSMovingAverageGain(0.5);

  runFramewatcherLoop = true;
  frameWatcher = std::thread{&FrameSource::frameWatcherFunction, this};
};

FrameSource::~FrameSource() {
  runFramewatcherLoop = false;
  frameWatcher.join();
};

void FrameSource::registerCallbackOnNewFrame(std::function<void(Frame *)> cb) { callbacks.push_back(cb); };

float FrameSource::getFPS() { return fps; };

void FrameSource::setFPSMovingAverageGain(float gain) { fpsMovingAverageGain = std::clamp(gain, 0.f, 1.f); };

void FrameSource::frameWatcherFunction() {
  while (runFramewatcherLoop) {
    Frame frame = getCurrentFrame();
    if (!frame.image.empty()) {
      steady_clock::time_point now = steady_clock::now();

      float elapsedSeconds = duration_cast<milliseconds>(now - lastFrameTimestamp).count() / 1000.f;
      // converting ourselves to keep ms precision

      if (elapsedSeconds != 0) {
        float singleFPS = 1 / elapsedSeconds;

        fps = (fps * fpsMovingAverageGain) + (singleFPS * (1 - fpsMovingAverageGain));
      };

      for (std::function<void(Frame *)> cb : callbacks) {
        if (cb != nullptr)
          cb(&frame);
      };
    };
  };
};