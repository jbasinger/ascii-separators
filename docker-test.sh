#!/bin/bash

export IMAGE_NAME='seps'

docker build -t "$IMAGE_NAME" .

docker container rm -f sep_test || true

docker run --rm \
  --name sep_test \
  -v "$(pwd)/src:/src" \
  -w "/src" \
  -a STDOUT \
  $IMAGE_NAME ./test.sh >result.log
