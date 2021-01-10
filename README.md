[![Build Status](https://travis-ci.org/edson-a-soares/producer_consumer.svg?branch=main)](https://travis-ci.org/edson-a-soares/producer_consumer)
[![codecov](https://codecov.io/gh/edson-a-soares/producer_consumer/branch/main/graph/badge.svg?token=BLDGUUQU8K)](https://codecov.io/gh/edson-a-soares/producer_consumer)

* [About Producer–Consumer problem](https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem)
* [Manually installing dependencies](docs/Manually_installing_dependencies.md)
* [Application dependencies](#application-dependencies)
* [Application basic directory structure](#application-basic-directory-structure)
* [Running with Docker](#running-with-docker)
* [Testing](#testing)

## Application dependencies

- CMake 3.7 or newer
- A C++14 compiler (i.e., GCC 6.3 or newer)
- Boost 1.7
- Poco C++ Libraries 1.9
- Google Test
- LCOV
- GCOV

## Application Basic Directory Structure

The basic directory structure is as follows:

```textmate

bin/                    all executables
lib/                    all libraries
data/                   all sort of application supporting files
    source/             source files that will be generated in runtime
    templates/          templates for messages exchanged between the process

scripts/                utility scripts for building
cmake/                  support files for CMake
docs/                   any additional documentation

Foundation/             project and make/build files for the Foundation module
    include/            all header files for the Foundation module
        Foundation/     header files for the Foundation module ports
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
./scripts/run-coverage-html-report.sh
```

### Useful links ###
* [Google Test](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)
* [gcov](http://manpages.ubuntu.com/manpages/xenial/man1/alpha-linux-gnu-gcov-5.1.html)

