FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
# change apt mirrors to servers which gives better download speed
RUN cp /etc/apt/sources.list /etc/apt/sources.list.bak && sed -i -r 's/http:\/\/(archive|security)\.ubuntu\.com/http:\/\/mirrors\.xtom\.nl/g' /etc/apt/sources.list
# install packages
RUN apt-get update && apt-get install -y apt-utils curl git gcc gdb vim perl make python3 openjdk-19-jdk cmake build-essential bear ninja-build bc module-assistant dkms doxygen subversion lcov libssl-dev libncurses-dev libboost-all-dev automake && rm -rf /var/lib/apt/lists/*

WORKDIR /
# build OClint
COPY ./src/ /oclint-repo
WORKDIR /oclint-repo/oclint-scripts
RUN ./remake-release; cp -r /oclint-repo/build/oclint-release /oclint-release

# Copy test
WORKDIR /
COPY ./tests/cpp /tests-cpp
COPY ./tests/java /tests-java



ENTRYPOINT ["tail", "-f", "/dev/null"]


