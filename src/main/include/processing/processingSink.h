#pragma once

#include "frame/frame.h"

class ProcessingSink {
public:
  ProcessingSink();

  ~ProcessingSink();

  bool accept(const Frame *frame);
};