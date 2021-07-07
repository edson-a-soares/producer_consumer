[![Build Status](https://travis-ci.org/edson-a-soares/producer_consumer.svg?branch=main)](https://travis-ci.org/edson-a-soares/producer_consumer)
[![codecov](https://codecov.io/gh/edson-a-soares/producer_consumer/branch/main/graph/badge.svg?token=BLDGUUQU8K)](https://codecov.io/gh/edson-a-soares/producer_consumer)

* [Application dependencies](#application-dependencies)
* [Manually installing dependencies](docs/Manually_installing_dependencies.md)
* [Application basic directory structure](#application-basic-directory-structure)
* [Running with Docker](#running-with-docker)
* [Testing](#testing)

## Application dependencies

- CMake 3.7 or newer
- A C++14 compiler (GCC 6.3 or newer)
- Boost 1.7
- Poco C++ Libraries 1.9
- Google Test
- LCOV
- GCOV

## Application basic directory structure

The basic directory structure is as follows:

```textmate

bin/                    all executables
lib/                    all libraries
data/                   all sort of application supporting files
    source/             source files that will be generated in runtime
    templates/          templates for the message exchanged between the processes

scripts/                utility scripts for building
cmake/                  supporting files for CMake
docs/                   any additional documentation

Foundation/             project and make/build files for the Foundation module
    include/            all header files for the Foundation module
    src/                source files for the Foundation module
    test/               project and make/build files for the Foundation testsuite
        Resources/      any supporting files for the tests
        Integration/    source files for the Foundation integration tests
        Unit/           source files for the Foundation unit tests
```

## Running with Docker

```bash
docker build . -t producer-consumer
docker run -it producer-consumer /bin/bash
cd /tmp/producer_consumer
```

## Testing

```bash
./scripts/run-all-tests.sh
```

##### Running coverage HTML report

```bash
./scripts/run-all-tests.sh
./scripts/run-coverage-html-report.sh
```

### Useful links ###
* [Producer–Consumer Problem](https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem)
* [Google Test](https://github.com/google/googletest/blob/master/googletest/docs)
* [gcov](http://manpages.ubuntu.com/manpages/xenial/man1/alpha-linux-gnu-gcov-5.1.html)
* [Doxygen](https://www.doxygen.nl/index.html)
