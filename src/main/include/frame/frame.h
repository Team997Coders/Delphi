#pragma once

#include "opencv2/core.hpp"
#include <chrono>

struct Frame {
  const cv::Mat image;
  const std::chrono::steady_clock::time_point captureTimestamp;

  Frame(cv::Mat image, std::chrono::steady_clock::time_point captureTimestamp)
      : image(image), captureTimestamp(captureTimestamp){};
};