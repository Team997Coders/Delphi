#pragma once

#include "frame/frame.h"

#include <string>

#include "frame/frameSource.h"

class CameraServerStreamInstance {

public:
  CameraServerStreamInstance(std::string name, FrameSource source);

  void consume(Frame frame);
};
