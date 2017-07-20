#!/bin/bash

PROJECT_ID="mooc-hub"
DOCKER_REPO="gcr.io/$PROJECT_ID"


IMAGE_SPEC=$DOCKER_REPO/pulltest:v0

docker build -t $IMAGE_SPEC .

gcloud docker -- push $IMAGE_SPEC
