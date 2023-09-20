FROM debian:stable
RUN apt-get update;apt-get install g++ nodejs
CMD bash