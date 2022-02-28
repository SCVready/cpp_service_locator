
# A C++ Service Locator

This repository contains:
- Source code: **src** and **inc** folders
- UnitTests: **test** folder
- Small example: **example** folder

## Example: VideoPlayer

In this example, an hypothetical VideoPlayer uses 2 services to accomplish the task of presenting frames in the screen: a decoder to decode the frames, and a logger to record all ongoing actions.

Those dependencies are not injected to the VideoPlayer, instead they are accessed via the ServiceLocator.

The main function chooses which implementation of the decoder (hardware or software decoder) and of the logger (file or network logger) to use.

*(this example don't include any real implementation apart of the ServiceLocator)*

## Building and running

    git clone

### Locally:
Install dependencies:

    sudo apt install -y build-essential libgtest-dev libgmock-dev cmake

Run and build:

    ./build.sh

### Docker container:

    docker run -it -v $(pwd):/service_locator --workdir /service_locator --user 1000:1000 scvready/ubuntu-gtest:latest ./build.sh