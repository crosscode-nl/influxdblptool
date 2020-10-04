# InfluxDB Line Writer Protocol

## Introduction

This library helps generating output according to the InfluxDB Line Writer Protocol.   

The protocol contains some escaping and encoding rules so it is easy to create files containing errors when doing this manually.

By using this fully tested library it becomes easy to generate data that conforms the InfluxDB Line Writer Protocol.   

See:
* [Line Protocol 1.8 Reference](https://docs.influxdata.com/influxdb/v1.8/write_protocols/line_protocol_reference/)
* [Line Protocol 2.0 Reference](https://v2.docs.influxdata.com/v2.0/reference/syntax/line-protocol/)

## Design choices

* An easy to use interface for using C++ output operators for consumers of this library.
* Modern C++ principles are used. 
* SOLID principles are used in order to create a maintainable and fully tested library.
* TDD is used to create new features.
* DRY principles are followed strongly.
* Expect and handle exceptions. Exceptions raised from this code are documented, but exceptions from calls into STL are
  not explicitly documented. This library defines only one exception influxdb::validation_exception. It's thrown when
  invalid input is given at any point. This library tries to validate input as early as possible. 

## Goals of and reasons for creating this library

* Refresh and update my C++ knowledge with more recent C++17 standards.
* I need this library for another project.
* Try out TDD development and SOLID principles using templates.
* Try out different unit test frameworks. 

## Examples

* [example01.cpp](examples/example01.cpp) This is a minimal example and explains some **important key concepts**.
* [example02.cpp](examples/example02.cpp) This example demonstrates adding fields and field types.  
* [example03.cpp](examples/example03.cpp) This example demonstrates adding a tag to the point.
* [example04.cpp](examples/example04.cpp) This example demonstrates removing a timestamp from a point.
* [example05.cpp](examples/example05.cpp) This example demonstrates setting a custom timestamp.
* [example06.cpp](examples/example06.cpp) This example demonstrates changing the timestamp resolution.
* [example07.cpp](examples/example07.cpp) This example demonstrates adding an INSERT prefix.
* [example08.cpp](examples/example08.cpp) This example demonstrates the points collection.
* [example09.cpp](examples/example09.cpp) This example demonstrates validation. 

## Installation

There are multiple ways to use and install this project. I will describe my favorite option only.

Consider the following example project: 

```cmake
cmake_minimum_required(VERSION 3.17)
project(example)

set(CMAKE_CXX_STANDARD 17)

add_executable(example main.cpp)
```

This will build a C++17 project with a main.cpp file.

Now to add this library to the project you can use [FetchContent CMake module](https://cmake.org/cmake/help/v3.18/module/FetchContent.html). 

The minimal requirement is to add: 

```cmake
include(FetchContent)
FetchContent_Declare(
        influxdblptool
        GIT_REPOSITORY https://github.com/crosscode-nl/influxdblptool
)
FetchContent_MakeAvailable(influxdblptool)
```

And to link against the library: 

```cmake
target_link_libraries(example influxdblptool)
```

Which will result in the following CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.17)
project(example)

include(FetchContent)
FetchContent_Declare(
        influxdblptool
        GIT_REPOSITORY https://github.com/crosscode-nl/influxdblptool
)
FetchContent_MakeAvailable(influxdblptool)

set(CMAKE_CXX_STANDARD 17)

add_executable(example main.cpp)
target_link_libraries(example influxdblptool)
```

Now see the examples to learn how to use this library.

TIP: Use `GIT_TAG` in `FetchContent_Declare` to pin a certain version to get reproducible builds.

## TODO

* Setup continuous integration.
* Code quality assessment by a 3rd party.

## License

MIT License

Copyright (c) 2019 CrossCode / P. Vollebregt

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
