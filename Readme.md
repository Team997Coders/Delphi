# Delphi
A lightweight alternative to both Limelight and PhotonVision for AprilTag localization in the FIRST Robotics Competition.

Currently incomplete!

## Goals

* Lightweight philosophy: No GUI and no OS image needed.
* All installations identical: The only installation-specific data used by Delphi are its string identifier, and the host team number, both of which are specified at compile time.
* Flexible: Many configurable options over NetworkTables, such as FPS cap, frame resolution, vision algorithms, camera calibrations, and more.
* Parity with Limelight and PhotonVision: All computer vision algorithms and functions found in those systems are implemented in Delphi as well.

## Building
Requires git (for downloading), cmake, openCV, and WPILib.

Most Linux package managers (and MacOS brew) can install cmake for you. Windows users should download binaries from https://cmake.org/download/.

OpenCV can often be found in package managers as `libopencv-dev`, but sometimes a manual installation is required. Unfortunately, this usually requires compiling it from source (found [here](https://github.com/opencv/opencv/releases)).

Dependencies on WPILib are only for the cscore, ntcore, and wpinet submodules. The following clones the WPILib repository, builds only the required modules, and installs the compiled objects such that CMake can find them in other projects:

```
$ git clone https://github.com/wpilibsuite/allwpilib.git
$ mkdir wpilib-cmake-build
$ cd wpilib-cmake-build
$ cmake ../allwpilib -DWITH_JAVA=OFF -DWIH_SHARED_LIBS=OFF -DWITH_WPIMATH=OFF -DWITH_WPILIB=OFF \
            -DWITH_EXAMPLES=OFF -DWITH_TESTS=OFF -DWITH_GUI=OFF -DWITH_SIMULATION_MODULES_OFF
$ make
$ sudo make install
```

Delphi is generally meant to be built in-place on the target coprocessor device, but cross-compiling (e.g. for an ARM64 Raspberry Pi) is possible using cmake argument `-DCMAKE_TOOLCHAIN_FILE="/path/to/file.cmake"`

To specify the string identifier for an instance of Delphi over NetworkTables and CameraServer, add the cmake argument `-DCONFIG_NAME="new_name"`. Otherwise, `defaultName` is used.

Run the following commands to quickly build Delphi from sources:
```
$ git clone https://github.com/Team997Coders/Delphi.git
$ cd Delphi
$ cmake .
$ make
```

## Licensing
Licensed under GPL-v3.0.