[![Build Status](https://travis-ci.org/edson-a-soares/producer_consumer.svg?branch=main)](https://travis-ci.org/edson-a-soares/producer_consumer)

* [About Producer–Consumer Problem](https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem)
* [Manually Installing Dependencies](docs/Manually_installing_dependencies.md)
* [Running with Docker](#running-with-docker)
* [Testing](#testing)

***

## Application dependencies

- CMake 3.7 or newer
- A C++14 compiler (i.e., GCC 6.3 or newer)
- Boost 1.7
- Poco C++ Libraries 1.9
- Google Test
- LCOV
- GCOV

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

