from ubuntu:latest

RUN apt update && apt upgrade -y && apt install build-essential clang clang-tools cmake curl unzip zip tar git ninja-build pkg-config libasio-dev libxdo-dev -y

RUN git clone --depth 1 https://github.com/microsoft/vcpkg && ./vcpkg/bootstrap-vcpkg.sh

RUN /vcpkg/vcpkg install crow gtest

RUN export VCPKG_ROOT=./vcpkg && export PATH=$VCPKG_ROOT:$PATH

RUN git clone https://github.com/fingerson/CppExperiment.git && cd CppExperiment && ./setup.sh && ./build.sh

cmd [ "/CppExperiment/build/Experiment" ]

expose 18080
#ENTRYPOINT [ "/bin/bash", "/CppExperiment/build/Experiment" ]