#pragma once

#include <string>

#include <frame/frameSource.h>

class NetworkTablesOutputInstance {
public:
  NetworkTablesOutputInstance(std::string name, FrameSource source);

  ~NetworkTablesOutputInstance();
};