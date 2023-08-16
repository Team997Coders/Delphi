#include "pipeline/cameraFrameSource.h"

CameraFrameSource::CameraFrameSource(uint cameraIndex) {
  capture = cv::VideoCapture{static_cast<int>(cameraIndex)};
  // gcc complains unless we're explicit here
};

Frame* CameraFrameSource::getCurrentFrame() {
  cv::OutputArray array{};

  capture.read(array);

  cv::Mat output = array.getMat();

  Frame&& frame = {output, std::chrono::steady_clock::now()};

  return &frame;
};