FROM ubuntu:18.04

RUN apt-get update
RUN apt-get -y install cmake
RUN apt-get -y install g++
RUN apt-get -y install libwxgtk3.0-dev
RUN apt-get -y install wget
RUN apt-get -y install p7zip
#rm -rf /var/lib/apt/lists/*

WORKDIR /root
RUN wget https://sourceforge.net/projects/mathgl/files/latest/download
RUN mv download mathgl.7z && p7zip -d mathgl.7z

ADD ./ /root/code
WORKDIR /root/code

#RUN cmake .
#RUN make
