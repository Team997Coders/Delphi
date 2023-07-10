#include "frame/cameraFrameSource.h"

CameraFrameSource::CameraFrameSource(uint cameraIndex) {
  capture = cv::VideoCapture{static_cast<int>(cameraIndex)};
  // gcc complains unless we're explicit here
};

Frame CameraFrameSource::getCurrentFrame() {
  cv::OutputArray array{};

  capture.read(array);

  return Frame{array.getMat(), std::chrono::steady_clock::now()};
};