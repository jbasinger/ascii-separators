FROM ubuntu

RUN apt-get update && apt-get install -yqq \
  build-essential curl less

WORKDIR /src
COPY src/ .