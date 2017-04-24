# To build use:
# docker build -t orian/cppenv:v1 .
FROM ubuntu:15.04
MAINTAINER Han Yu <hanyu0612@gmail.com>

LABEL description="A linux C++ python build environment."

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
  software-properties-common \
  python-software-properties 
RUN add-apt-repository ppa:fkrull/deadsnakes
RUN apt-get install -y \
  gcc \
  clang \
  cmake \
  libgtest-dev \
  libgoogle-glog-dev \
  libboost-all-dev \
  g++ `#Fb folly deps` \
  automake \
  autoconf \
  autoconf-archive \
  libtool \
  libboost-all-dev \
  libevent-dev \
  libdouble-conversion-dev \
  libgoogle-glog-dev \
  libgflags-dev \
  liblz4-dev \
  liblzma-dev \
  libsnappy-dev \
  make \
  zlib1g-dev \
  binutils-dev \
  libjemalloc-dev \
  libssl-dev \
  libiberty-dev \
  gdb \
  g++-multilib \
  python2.7

ENV LD_LIBRARY_PATH=/libs
ENV CPLUS_INCLUDE_PATH=/libs/include

RUN mkdir /src
RUN mkdir /build
WORKDIR /build

CMD ["/bin/bash"]
