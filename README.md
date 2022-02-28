
# A C++ Service Locator

This repository contains:
- Source code: **src** and **inc** folders
- UnitTests: **test** folder
- Small example: **example** folder

It can be easily integrated by copying the header and the source file into any C++11/14/17 project.

## Usage:

1. Add the following lines to the file/s that will use the ServiceLocator to register services ( this allows the compiler to know where to find the definition of the ServiceLocator's internal static data)

        template <typename Type>
        extern std::function<std::shared_ptr<Type>(void)> ServiceLocator<Type>::m_service_retriever;


2. Register a service in the ServiceLocator:

    Declare the std::function that the locator will use to return the object when it's requested:
    i.e. a lambda that creates new objects:

        std::function<std::shared_ptr<NewService>(void)> service_retriever = [](){ return std::make_shared<NewService>(); };

    Register the service passing as a parameter the created service_retriever function:

        ServiceLocator<NewService>::RegisterService( service_retriever );

3. Access the object via the ServiceLocator:

        ServiceLocator<NewService>::GetService()

4. Remove the Service from the ServiceLocator:

        ServiceLocator<NewService>::RemoveService()

## Example: VideoPlayer

In this example, an hypothetical VideoPlayer uses 2 services to accomplish the task of presenting frames in the screen: a decoder to decode the frames, and a logger to record all ongoing actions.

Those dependencies are not injected to the VideoPlayer, instead they are accessed via the ServiceLocator.

The main function chooses which implementation of the decoder (hardware or software decoder) and of the logger (file or network logger) to use.

*(this example don't include any real implementation apart of the ServiceLocator)*

## Building/running: tests and the example
Clone the repo

    git clone https://github.com/SCVready/cpp_service_locator
    cd cpp_service_locator

### Build/running locally (Linux/Ubuntu20.04):

Install dependencies:

    sudo apt install -y build-essential libgtest-dev libgmock-dev cmake

Run and build:

    ./build.sh

### Build/running in Docker (Linux):

    docker run -it -v $(pwd):/service_locator --workdir /service_locator --user 1000:1000 scvready/ubuntu-gtest:latest ./build.sh