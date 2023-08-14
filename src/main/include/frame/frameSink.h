#pragma once

#include "frame/frame.h"

class FrameSink {
public:
  virtual bool accept(Frame frame) = 0;
};