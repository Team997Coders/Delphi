#pragma once

#include "frame/frameSource.h"

#include "opencv2/videoio.hpp"

class CameraFrameSource : FrameSource {
public:
  CameraFrameSource(uint cameraIndex);

  Frame getCurrentFrame();

private:
  cv::VideoCapture capture;
};