# Introduction

* [About](https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem)
* [Application dependencies](#application-dependencies)
* [Running tests](#running-tests)

***

## Application dependencies

- CMake 3.7 or newer
- A C++14 compiler (i.e., GCC 6.3 or newer)
- Boost 1.7
- Poco C++ Libraries 1.9
- Google Test
- LCOV

#### Installing main dependencies

[GCC](https://gcc.gnu.org/gcc-6/changes.html)

```bash
sudo apt-add-repository ppa:ubuntu-toolchain-r/test  
sudo apt-get update --yes --force-yes  
sudo apt-get install g++6.3 gcc-6
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 60 --slave /usr/bin/g++ g++ /usr/bin/g++-5
```

[Poco C++ Libraries](https://pocoproject.org/releases/poco-1.9.0/poco-1.9.0-all.tar.gz)

```bash
tar -xf poco-1.9-all.tar.gz  
cd /path/to/poco-1.9-all  
./configure --no-tests --no-samples --typical  
sudo make
sudo make install 
```

[Boost C++ Libraries](https://www.boost.org/users/history/version_1_70_0.html)

```bash
tar -xf boost_1_70_0.tar.gz  
cd boost_1_70_0  
./bootstrap.sh --with-libraries=program_options,system,locale,filesystem,chrono,thread
./b2 --link=shared --runtime-link=shared --variant=release
./b2 install
```

Boost B2 will leave Boost binaries in the lib/ subdirectory of your installation prefix.
You will also find a copy of the Boost headers in the include/ subdirectory of the installation prefix,
so you can henceforth use that directory as an #include path in place of the Boost root directory.

[Google Test (GTest)](https://github.com/google/googletest)

```bash
sudo apt-get install libgtest-dev
```

[LCOV](https://github.com/linux-test-project/lcov)

```
git clone https://github.com/linux-test-project/lcov.git
make install
```

## Running tests

```bash
./scripts/run-all-tests.sh
```

##### Running tests LCOV report

```bash
./scripts/run-tests-lcov-report.sh
```

##### Running tests with coverage report

```bash
./scripts/run-tests-coverage-report.sh
```

### Useful links ###
* [Google Test](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)

