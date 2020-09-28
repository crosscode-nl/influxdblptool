# InfluxDB Line Writer Protocol

## Introduction

This library helps generating output according to the InfluxDB Line Writer Protocol.   

The protocol contains some escaping and encoding rules so it is easy to create files containing errors when doing this manually.

By using this fully tested library it becomes easy to generate data that conforms the InfluxDB Line Writer Protocol.   

See:
* [Line Protocol 1.8 Reference](https://docs.influxdata.com/influxdb/v1.8/write_protocols/line_protocol_reference/)
* [Line Protocol 2.0 Reference](https://v2.docs.influxdata.com/v2.0/reference/syntax/line-protocol/)

## License

MIT
Copyright 2020 CrossCode / P. Vollebregt 

See the file [LICENSE](LICENSE).

## Design choices

* An easy to use interface for using C++ output operators for consumers of this library.
* Modern C++ principles are used. 
* SOLID principles are used in order to create a maintainable and fully tested library.
* TDD is used to create new features.
* DRY principles are followed strongly.
* Expect and handle exceptions. Exceptions raised from this code are documented, but exceptions from calls into STL are
  not explicitly documented. This library defines only one exception influxdb::validation_exception. It's thrown when
  invalid input is given at any point. This library tries to validate input as early as possible. 

## Goals of creating this library

* Improve C++ knowledge with more recent C++17 standards.
* I needed this library for another project.
* Try TDD development and SOLID principles using templates.

## Examples

* [example01.cpp](examples/example01.cpp) This is a minimal example and explains some key concepts.
* [example02.cpp](examples/example02.cpp) This example demonstrates adding fields and field types.  
* [example03.cpp](examples/example03.cpp) This example demonstrates adding a tag to the point.
* [example04.cpp](examples/example04.cpp) This example demonstrates removing a timestamp from a point.

Not all examples are created yet. See the [unit tests](tests/serializers_tests.cpp) for more examples. 

## TODO

* Add a fluent interface.
* Allow setting timestamp resolution and prefix on point.
* Add comments for Doxygen doc generation.
* Add more examples.
* Setup continuous integration.
* Code quality assessment by a 3rd party.
