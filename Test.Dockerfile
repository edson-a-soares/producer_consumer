FROM edsonsoares/boost_poco

ENV DEBIAN_FRONTEND noninteractive

# Install most basic application dependencies
RUN apt-get update -qq \
    && dpkg --add-architecture i386 \
    && apt-get update \
	&& apt-get install -yq --no-install-recommends \
	    doxygen \
	    gcovr \
        # Google Mocks
        google-mock \
		# Google Tests
		libgtest-dev

# It compiles and makes available (install) Google Test
RUN cd /usr/src/gtest \
    && cmake . \
    && make && cp *.a /usr/lib

# It imports and makes the application available
COPY . /tmp/producer_consumer
RUN cd /tmp/producer_consumer \
    && mkdir cmake-build \
    && cd cmake-build \
    && cmake .. \
        -DENABLE_TESTS=ON \
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE:-Debug} \
    && cd /tmp/producer_consumer \
    && cmake --build cmake-build
