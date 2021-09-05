FROM edsonsoares/boost_poco

ENV DEBIAN_FRONTEND noninteractive

# Install most basic application dependencies
RUN apt-get update -qq \
    && dpkg --add-architecture i386 \
    && apt-get update \
	&& apt-get install -yq --no-install-recommends \
	    doxygen \
	    gcovr \
        google-mock \
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
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE:-Release} \
    && cd /tmp/producer_consumer \
    && cmake --build cmake-build \
    && cd cmake-build && make install

# Add the Apache Connector file configuration file to the image
COPY data/settings/poco.load /etc/apache2/mods-available/poco.load

ENV LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

RUN a2enmod poco && /usr/sbin/apache2ctl restart

EXPOSE 80
CMD ["/usr/sbin/apachectl", "-DFOREGROUND"]
