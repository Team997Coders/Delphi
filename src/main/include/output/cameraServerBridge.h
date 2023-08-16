#pragma once

#include "pipeline/frame.h"

#include <string>

#include "cscore_oo.h"
#include "cscore_raw_cv.h"

struct CameraServerStreamConfig {
  uint16_t width_px;
  uint16_t height_px;
  uint16_t reportedFPS;
};

class CameraServerStreamInstance {

public:
  CameraServerStreamInstance(std::string name, uint16_t tcpPort, CameraServerStreamConfig config);

  bool accept(Frame frame);

private:
  cs::MjpegServer mjpegSv;
  cs::RawCvSource imgSource;
};
