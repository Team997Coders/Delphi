#pragma once

#include "frame/frameSource.h"

class FrameSink : FrameSource {
public:
  virtual bool accept(const Frame *frame) = 0;
};