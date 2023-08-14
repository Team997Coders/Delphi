#include "output/cameraServerBridge.h"

CameraServerStreamInstance::CameraServerStreamInstance(std::string name, uint16_t tcpPort,
                                                       CameraServerStreamConfig config) {
  std::string combinedName = "delphi_" + name;
  mjpegSv = cs::MjpegServer{combinedName, tcpPort};

  imgSource = cs::RawCvSource{combinedName, cs::VideoMode::PixelFormat::kBGR, config.width_px, config.height_px,
                              config.reportedFPS};

  mjpegSv.SetSource(imgSource);
}

bool CameraServerStreamInstance::accept(Frame frame) {
  imgSource.PutFrame(frame.image);
  return imgSource.IsEnabled();
}