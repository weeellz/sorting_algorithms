FROM debian:sid-20200803-slim as dev-igame

RUN apt-get update && apt-get install -y --no-install-recommends \
         build-essential cmake ninja-build gdb git python3 clang-format python3-pip

RUN pip install numpy

