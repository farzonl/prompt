FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt install -y --no-install-recommends \
    build-essential cmake openssl ca-certificates

# Set the working directory to root (ie $HOME)
WORKDIR root

COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release
RUN make -C./build

RUN ./build/test/WordFreq_TEST

RUN ./build/src/WordFreq test/files/beastie.txt test/files/iverson.txt