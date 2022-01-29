# Reborn library

## Introduction
This library main goal is to provide a standard library that is nicer to use than the default C/C++ one.

## Requirements

To build this library, you will need the following tools :
* CMake
* (_On Windows_) MSVC
* (_On Linux/Mac_) Clang or GCC
* (_optional_) Ninja

In the future, I would like to offer an alternative to CMake that would only require a C/C++ compiler. In the meantime, I rely on CMake as I don't want to take care of that currently.

Ninja is an optional dependency that can increase build time a bit.

## Building

__On Windows__

Building the library is quite simple. First of all, configure the project with the following command :
```
cmake (-G Ninja) -Bcmake-build -DCMAKE_BUILD_TYPE=(Debug|Release|RelWithDebInfo) .
```

(Note that if Ninja is not used, this will default to MSBuild that is a multi-configuration generator. Thus, the `CMAKE_BUILD_TYPE=(Debug|Release|RelWithDebInfo)` option is not necessary).

Once the configuration succeeded, building the library is as simple as :
```
cmake --build cmake-build --target libreborn --parallel
```

If you didn't use the Ninja generator, you can specify a build configuration with `--config (Debug|Release|RelWithDebInfo)`

__On Linux / Mac__

Not supported yet