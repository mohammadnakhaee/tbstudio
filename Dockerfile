FROM ubuntu:18.04
RUN apt-get update
RUN apt-get -y install make
RUN apt-get -y install libwxgtk3.0-dev
RUN apt-get -y install g++
#rm -rf /var/lib/apt/lists/*
ADD ./ /root/code
WORKDIR /root/code
#RUN make
