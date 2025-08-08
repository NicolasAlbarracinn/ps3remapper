FROM ubuntu:18.04

# Avoid warnings about using apt-get without updating
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install basic dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    subversion \
    wget \
    flex \
    bison \
    gperf \
    python3 \
    python3-pip \
    python3-setuptools \
    cmake \
    ninja-build \
    ccache \
    libffi-dev \
    libssl-dev \
    dfu-util \
    autoconf \
    automake \
    texinfo \
    pkg-config \
    zlib1g-dev \
    libtool \
    libgmp-dev \
    libmpfr-dev \
    libmpc-dev \
    make \
    file \
    patch \
    libelf-dev \
    libtool \
    libtool-bin \
    libncurses5-dev \
    libncursesw5-dev \
    gettext \
    texinfo \
    bzip2 \
    flex \
    bison \
    gcc-multilib \
    g++-multilib \
    build-essential \
    python2.7 \
    python2.7-dev \
    python-dev \
    rsync \
    curl \
    unzip \
    m4 \
    perl \
    zstd \
    xxd

# Set up PS3 development environment
ENV PS3DEV=/usr/local/ps3dev
ENV PSL1GHT=$PS3DEV
ENV PATH=$PATH:$PS3DEV/bin:$PS3DEV/ppu/bin:$PS3DEV/spu/bin:$PS3DEV/host/ppu/bin:$PS3DEV/host/spu/bin
ENV CPATH=/usr/local/include
ENV LIBRARY_PATH=/usr/local/lib
ENV PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
ENV PYTHONPATH=/usr/local/lib/python3/site-packages
ENV PYTHON=/usr/bin/python2.7

# Set up Python 2.7 as the default python
RUN update-alternatives --install /usr/bin/python python /usr/bin/python2.7 1 && \
    update-alternatives --set python /usr/bin/python2.7
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# Create PS3DEV directory and set permissions
RUN mkdir -p $PS3DEV && \
    chmod -R 777 $PS3DEV && \
    ln -sf /usr/bin/python2.7-config /usr/bin/python-config

# Clone PS3 toolchain
RUN git clone https://github.com/ps3dev/ps3toolchain.git && \
    cd ps3toolchain && \
    chmod +x toolchain.sh && \
    chmod +x depends/check-*.sh

# Build each component separately to better handle errors
RUN cd ps3toolchain && \
    ./depends/check-gmp.sh && \
    ./depends/check-autoconf.sh && \
    ./depends/check-automake.sh && \
    ./depends/check-pkg-config.sh && \
    ./depends/check-makeinfo.sh && \
    ./depends/check-wget.sh && \
    ./depends/check-libelf.sh && \
    ./depends/check-libtool.sh && \
    ./depends/check-ncurses.sh && \
    ./depends/check-python.sh && \
    ./depends/check-zlib.sh && \
    ./depends/check-make.sh && \
    ./depends/check-patch.sh

# Now run the toolchain build
RUN cd ps3toolchain && \
    ./toolchain.sh

# Set working directory
WORKDIR /src

# Command to run when container starts
CMD ["/bin/bash"]
