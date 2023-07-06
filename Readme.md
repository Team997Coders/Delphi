# Delphi
A lightweight alternative to both Limelight and PhotonVision for AprilTag localization in the FIRST Robotics Competition.

Currently incomplete!

## Goals

* Lightweight philosophy: No GUI and no OS image needed.
* All installations identical: The only installation-specific data used by Delphi is its `NT_NAME`, which is specified *before compile-time*.
* Flexible: Many configurable options over NetworkTables, such as FPS cap, frame resolution, vision algorithms, camera calibrations, and more.
* Parity with Limelight and PhotonVision: All computer vision algorithms and functions found in those systems are implemented in Delphi as well.

## Building
Requires git (for downloading), cmake, and OpenCV sources. (Dependencies on WPILib not yet required in this version, but are upcoming)

Most Linux package managers (and MacOS brew) can install cmake for you. Windows users should download binaries from https://cmake.org/download/.

OpenCV sources can often be found in package managers as `libopencv-dev`, but sometimes a manual installation is required. Unfortunately, this usually requires compiling it from source (found [here](https://github.com/opencv/opencv/releases)).

Delphi is generally meant to be built in-place on the target coprocessor device, but cross-compiling (e.g. for an ARM64 Raspberry Pi) is possible using cmake argument `-DCMAKE_TOOLCHAIN_FILE="/path/to/file.cmake"`

To specify the `NT_NAME` (identifier for NetworkTables associated with an instance of Delphi), add the cmake argument `-DNT_NAME="new_name"`.

```
$ git clone https://github.com/Team997Coders/Delphi.git
$ cd Delphi
$ cmake .
$ make
```

## Licensing
Licensed under GPL-v3.0.