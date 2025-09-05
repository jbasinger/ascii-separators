#!/bin/bash

export IMAGE_NAME='seps'

docker build -t "$IMAGE_NAME" .

docker run -it --rm \
  --hostname "ascii" \
  -v "$(pwd)/src:/src" \
  --entrypoint /bin/bash \
  $IMAGE_NAME