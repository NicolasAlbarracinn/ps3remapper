#!/bin/bash

# Build the Docker image
echo "Building Docker image..."
docker build -t ps3dev .

# Run the container with the current directory mounted
echo "Running container..."
docker run -it --rm -v "$(pwd):/src" ps3dev

# Note: Inside the container, you can run:
# make clean && make
