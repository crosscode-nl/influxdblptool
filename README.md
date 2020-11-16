# InfluxDBLPTool 
[![GitHub version](https://badge.fury.io/gh/crosscode-nl%2Finfluxdblptool.svg)](https://badge.fury.io/gh/crosscode-nl%2Finfluxdblptool)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/crosscode-nl/influxdblptool.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/crosscode-nl/influxdblptool/context:cpp)
[![Build Status](https://travis-ci.com/crosscode-nl/influxdblptool.svg?branch=master)](https://travis-ci.com/crosscode-nl/influxdblptool) 
[![Build status](https://ci.appveyor.com/api/projects/status/eje2c2beookmn93b?svg=true)](https://ci.appveyor.com/project/crosscode-nl/influxdblptool)
[![Standard](https://img.shields.io/badge/c%2B%2B-17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Introduction

InfluxDBLPTool - a C++17 library - helps generating InfluxDB Line Protocol formatted output.   

The protocol contains some escaping and encoding rules so it is easy to create files containing errors when doing this manually.

By using this fully tested library it becomes easy to generate data that conforms to the InfluxDB Line Protocol.   

See:
* [Line Protocol 1.8 Reference](https://docs.influxdata.com/influxdb/v1.8/write_protocols/line_protocol_reference/)
* [Line Protocol 2.0 Reference](https://v2.docs.influxdata.com/v2.0/reference/syntax/line-protocol/)

## Installation

There are multiple ways to add this library to your project. There are too many tools for C++ to describe them all. 

I will describe two methods, both for CMake users. 

The first method will download the source code and build against it, the second will use a system installed version of 
the library.

The first method works best in CI/CD pipelines without to much hassle. This is therefore the preferred method.

### CMake FetchContent (Preferred)

This method emulates dependency management of more modern languages and build systems like Rust+Cargo and Go as best as 
it can.

Consider the following example project: 

```cmake
cmake_minimum_required(VERSION 3.17)
project(example)

add_executable(example main.cpp)
target_compile_features(example PUBLIC cxx_std_17)
```

This will build a C++17 project with a main.cpp file.

Now to add this library to the project you can use the 
[FetchContent CMake module](https://cmake.org/cmake/help/v3.18/module/FetchContent.html). 

The minimal requirement is to add: 

```cmake
include(FetchContent)
FetchContent_Declare(
        influxdblptool
        GIT_REPOSITORY https://github.com/crosscode-nl/influxdblptool
        GIT_TAG v2.0.0
)
FetchContent_MakeAvailable(influxdblptool)
```

And to link against the library: 

```cmake
target_link_libraries(example influxdblptool)
```

This will result in the following CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.17)
project(example)

add_executable(example main.cpp)
target_compile_features(example PUBLIC cxx_std_17)

include(FetchContent)
FetchContent_Declare(
        influxdblptool
        GIT_REPOSITORY https://github.com/crosscode-nl/influxdblptool
        GIT_TAG v2.0.0
)
FetchContent_MakeAvailable(influxdblptool)
target_link_libraries(example influxdblptool)
```

Now see the examples to learn how to use this library.

*TIP: Use `GIT_TAG` in `FetchContent_Declare` to pin a certain version to get reproducible builds.*

### CMake Find_Package

This method will use CMake's find_package.

The first step is to install the library on the system.

#### Installing onto the system

This method requires InfluxDBLPTool to be build and installed on the system.

```bash
git clone https://github.com/crosscode-nl/influxdblptool
mkdir influxdblptool-build
cd influxdblptool-build
cmake ../influxdblptool -DCMAKE_BUILD_TYPE=Release
sudo make install 
```

Or if you want to install it somewhere in you home directory, for example: 

```bash
git clone https://github.com/crosscode-nl/influxdblptool
mkdir influxdblptool-build
cd influxdblptool-build
cmake ../influxdblptool -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/home/developer/libraries
make install 
```

#### Using the installed library

Consider the following example project: 

```cmake
cmake_minimum_required(VERSION 3.17)
project(example)

add_executable(example main.cpp)
target_compile_features(example PUBLIC cxx_std_17)
```

To use an installed library you just have to add: 

```cmake
find_package(InfluxDBLPTool 2.0.0 REQUIRED)
target_link_libraries(example InfluxDBLPTool::influxdblptool)
```

This will result in the following CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.17)
project(example)

add_executable(example main.cpp)
target_compile_features(example PUBLIC cxx_std_17)

find_package(InfluxDBLPTool 2.0.0 REQUIRED)
target_link_libraries(example InfluxDBLPTool::influxdblptool)
```

When you installed the library in a different location then you have to add 
`-DCMAKE_PREFIX_PATH=/home/developer/libraries` to your 
[CMake command](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html). 

## Examples

The interface of the library looks like this: 

```cpp        
    // A point cannot be created without a field, so it takes a mandatory field via it's constructor.
    std::cout << (point("performance"s,field("cpu_load"s,50u)) << tag("host"s,"localhost"s) << field("mem_free"s,10u));     
```

Examine the following examples to learn how to use this library.

* [example01.cpp](examples/example01.cpp) This is a minimal example and explains some **important key concepts**.
* [example02.cpp](examples/example02.cpp) This example demonstrates adding fields and field types.  
* [example03.cpp](examples/example03.cpp) This example demonstrates adding a tag to the point.
* [example04.cpp](examples/example04.cpp) This example demonstrates removing a timestamp from a point.
* [example05.cpp](examples/example05.cpp) This example demonstrates setting a custom timestamp.
* [example06.cpp](examples/example06.cpp) This example demonstrates changing the timestamp resolution.
* [example07.cpp](examples/example07.cpp) This example demonstrates adding an INSERT prefix.
* [example08.cpp](examples/example08.cpp) This example demonstrates the points collection.
* [example09.cpp](examples/example09.cpp) This example demonstrates validation. 
* [example10.cpp](examples/example10.cpp) This example demonstrates to_string serialization

## Design choices

* An easy to use interface for using C++ output operators for consumers of this library.
* Modern C++ principles are used. 
* SOLID principles are used in order to create a maintainable and fully tested library.
* TDD is used to create new features.
* DRY principles are followed strongly.
* Expect and handle exceptions. Exceptions raised from this code are documented, but exceptions from calls into STL are
  not explicitly documented. This library defines only one exception influxdb::validation_exception. It's thrown when
  invalid input is given at any point. This library tries to validate input as early as possible. 

## Reasons for creating this library

* Update my C++ knowledge with the new features added in the C++17 standard.
* I needed this library for another project.
* Try out TDD development and SOLID principles using templates.
* Try out different unit test frameworks.
* Learn about different installation strategies of C++ libraries.  
* Give something back to the open source community.
* Demonstrate my C++ knowledge and skills.

## Lessons learned

During the creation of this library I have learned some lessons. I'd like to share some of the lessons: 

* Initially I designed the library using (smart) pointers to mimic who I would write an application in C# using SOLID
principles. However, C++ is designed for speed, and to achieve this speed you need to design for make use of 
cache locality as much as possible. Also, heap allocations are slow, so that's another reason to avoid them if possible. 
I refactored the library code so it doesn't use (smart) pointers anymore. All SOLID principles are established using 
templates. 
* I want it for users to make it as easy as possible to use this library. However, there are too many tools to describe
each and every way of using this library. I'm opinionated about CMake. I don't like its syntax or documentation but 
it works well, and makes it very easy to write a build script that works on a lot of platforms. It also has a pretty
good way of dealing with dependencies. 
* I developed this library using GCC. When I create the CI scripts the library did not compile on MSVC and Clang. It
seems that GCC isn't following the standard very strictly. Therefore it allows more invalid code to compile correctly. 
At least, that's what I'm told. Clang is pretty strict. MSVC uses a standard library written by Microsoft. This can also
cause compilation errors because of include files that need to be included, while the other compilers don't think so
or even recommend removing them. 
* The (fluent) interface of the library is based on the iostream interface and uses the output operator just like the 
standard library does for iostream. Some people don't like this. They will tell you about it. Next time I design a more
language base fluent interface.
* I like doctest & Catch2 as unit test frameworks. Doctest is very similar to Catch2, but it's lighter weight. They are 
simple, structured and create readable unit tests. Initially I started testing with GTest & GMock but it caused complex 
unit tests that would not allow for a nice structure. Also it suited the (smart) pointer based SOLID principles more 
than the templated approach.  
* I find C++ pretty ugly. Rust has a lot of the same properties as C++, but it allows for a cleaner syntax and is 
a safer language. If I needed to create something with the properties of C++ I would would do it in Rust. This library
is needed in an existing C++ project though. Using Rust would have meant I needed to create a C interface to create 
an ABI that could be used in C++. To make it more C++ again, that interface should than again be wrapped in a more C++ 
interface. In other words: that would have created a lot more work.

## License

MIT License

Copyright (c) 2020 CrossCode / P. Vollebregt

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the 
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the 
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
