[![Build Status](https://app.travis-ci.com/edson-a-soares/producer_consumer.svg?branch=main)](https://app.travis-ci.com/edson-a-soares/producer_consumer)
[![codecov](https://codecov.io/gh/edson-a-soares/producer_consumer/branch/main/graph/badge.svg?token=BLDGUUQU8K)](https://codecov.io/gh/edson-a-soares/producer_consumer)

* [Application dependencies](#application-dependencies)
* [Manually installing dependencies](docs/Manually_installing_dependencies.md)
* [Application basic directory structure](#application-basic-directory-structure)
* [Running with Docker](#running-with-docker)
* [Testing](#testing)
* [Documentation](https://edson-a-soares.github.io/producer_consumer/doxygen/html)

## Application dependencies

- CMake 3.7 or newer
- A C++14 compiler (GCC 6.3 or newer)
- Boost 1.70.0
- Poco C++ Libraries 1.9
- Google Test
- Google Mock
- LCOV
- GCOV
- Doxygen

## Application basic directory structure

The basic directory structure is as follows:

```textmate

bin/                    all executables
lib/                    all libraries
data/                   all sort of application supporting files
    source/             source files that will be generated in runtime
    templates/          templates for the messages exchanged between the processes

scripts/                utility scripts for building
cmake/                  supporting files for CMake
docs/                   any additional documentation

Foundation/             project and make/build files for the Foundation module
    include/            all header files for the Foundation module
        Adapter/        all ConsumerDaemon module adapters
        Foundation/     all ConsumerDaemon module ports
    src/                source files for the Foundation module
    test/               project and make/build files for the Foundation testsuite
        Resources/      any supporting files for the tests
        Integration/    source files for the Foundation integration tests
        Unit/           source files for the Foundation unit tests

Consumer/               project and make/build files for the Consumer module
    include/            all header files for the Consumer module
        Adapter/        all Consumer module adapters
        Consumer/       all Consumer module ports
    src/                source files for the Consumer module
    test/               project and make/build files for the Consumer testsuite
        Resources/      any supporting files for the tests
        Integration/    source files for the Consumer integration tests
        Unit/           source files for the Consumer unit tests
        E2E/            source files for the Consumer end-to-end tests

ConsumerDaemon/         project and make/build files for the ConsumerDaemon module
    include/            all header files for the ConsumerDaemon module
        Adapter/        all ConsumerDaemon module adapters
        ConsumerDaemon/ all ConsumerDaemon module ports
    src/                source files for the ConsumerDaemon module
    test/               project and make/build files for the ConsumerDaemon testsuite
        Resources/      any supporting files for the tests
        Integration/    source files for the ConsumerDaemon integration tests
        Unit/           source files for the ConsumerDaemon unit tests
        E2E/            source files for the ConsumerDaemon end-to-end tests

Producer/               project and make/build files for the Producer module
    include/            all header files for the Producer module
        Adapter/        all Producer module adapters
        Producer/       all Producer module ports
    src/                source files for the Producer module
    test/               project and make/build files for the Producer testsuite
        Resources/      any supporting files for the tests
        Integration/    source files for the Producer integration tests
        Unit/           source files for the Producer unit tests
        E2E/            source files for the Producer end-to-end tests
```

## Running with Docker

```bash
docker build . -t producer-consumer
docker run --name producer-consumer -p8080:80 -d producer-consumer
docker exec -it producer-consumer /bin/bash
docker stop producer-consumer
```

## Testing

```bash
docker build . -t producer-consumer-test -f Test.Dockerfile
docker run producer-consumer-test /bin/bash -c "cd /tmp/producer_consumer; ./scripts/run-all-tests.sh"
```

##### Running coverage HTML report

```bash
./scripts/run-all-tests.sh
./scripts/run-coverage-html-report.sh
```

### Useful links ###
* [Producer–Consumer Problem](https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem)
* [Ports and Adapters Architecture](https://en.wikipedia.org/wiki/Hexagonal_architecture_(software))
* [Google Test](https://github.com/google/googletest/blob/master/googletest/docs)
* [gcov](http://manpages.ubuntu.com/manpages/xenial/man1/alpha-linux-gnu-gcov-5.1.html)
* [Doxygen](https://www.doxygen.nl/index.html)
