# Simple build environment for PS3 plugin
FROM ubuntu:20.04

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install basic build tools and minimal PS3 dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    curl \
    make \
    gcc \
    autoconf \
    automake \
    texinfo \
    pkg-config \
    zlib1g-dev \
    libtool \
    libgmp-dev \
    libmpfr-dev \
    libmpc-dev \
    file \
    patch \
    libelf-dev \
    libtool-bin \
    libncurses5-dev \
    libncursesw5-dev \
    gettext \
    bzip2 \
    gcc-multilib \
    g++-multilib \
    bison \
    flex \
    gperf \
    python2.7 \
    python2.7-dev \
    python-dev \
    && rm -rf /var/lib/apt/lists/*

# Set up environment variables
ENV PS3DEV=/usr/local/ps3dev
ENV PSL1GHT=$PS3DEV
ENV PATH=$PATH:$PS3DEV/bin:$PS3DEV/ppu/bin:$PS3DEV/spu/bin

# Create PS3DEV directory
RUN mkdir -p /usr/local/ps3dev

# Create working directory
WORKDIR /src

# Copy source files
COPY . .

# Default command
CMD ["/bin/bash"]
