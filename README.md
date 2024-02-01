# Simplest 2D Engine on Earth

This is an attempt on making a 2D game with my own engine in C++.

## Building

With CMake on Linux.

```sh
mkdir build && cd build && cmake .. && make
```

MinGW on Windows.

```sh
mkdir build && cd build && cmake -G "MinGW Makefiles" .. && mingw32-make
```

Visual Studio on Windows.

```sh
mkdir build && cd build && cmake -G "Visual Studio 17 2022" ..
```