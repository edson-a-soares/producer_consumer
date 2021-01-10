FROM edsonsoares/poco:1.9-debian

ENV DEBIAN_FRONTEND noninteractive

ENV BOOST_DOWNLOAD_URL https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.gz
ENV BOOST_SHA256 882b48708d211a5f48e60b0124cf5863c1534cd544ecd0664bb534a4b5d506e9

# Download and install Boost 1.7
RUN curl -fsSL "${BOOST_DOWNLOAD_URL}" -o /tmp/boost_1_70_0.tar.gz \
    && echo "$BOOST_SHA256  /tmp/boost_1_70_0.tar.gz" | sha256sum -c - \
    && tar --directory /tmp -xzf /tmp/boost_1_70_0.tar.gz \
    && cd /tmp/boost_1_70_0 && ./bootstrap.sh --with-libraries=program_options,system,locale,filesystem,chrono,thread \
    && ./b2 --link=shared --runtime-link=shared --variant=release \
    && ./b2 install \
    && rm -rf /tmp/boost_1_70_0 /tmp/boost_1_70_0.tar.gz

# Install most basic application dependencies
RUN apt-get update -qq \
    && dpkg --add-architecture i386 \
    && apt-get update \
	&& apt-get install -yq --no-install-recommends \
	    gcovr \
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
    && cd /tmp/producer_consumer \
    && cmake --build cmake-build
