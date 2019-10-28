FROM ubuntu:18.04
RUN apt-get update
RUN apt-get -y install make
#rm -rf /var/lib/apt/lists/*
ADD ./ /root/code
WORKDIR /root/code
