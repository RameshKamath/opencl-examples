IMAGE_NAME="opencl_image"
CONTAINER_NAME="${IMAGE_NAME}_container"
VOLUME_HOST_PATH="$(pwd)"
VOLUME_CONTAINER_PATH="/home/opencl-examples"

FOUND_IMAGE="$(docker image ls | grep ${IMAGE_NAME})"
FOUND_CONTAINER="$(docker ps -a | grep ${CONTAINER_NAME})"

if [ "${FOUND_IMAGE}" = "" ]; then
    echo "Image not found"
    # Create image
    docker image build -q --tag ${IMAGE_NAME} ./Dockerfile
    echo "Image built"
fi
echo ${FOUND_CONTAINER}
if [ "${FOUND_CONTAINER}" = "" ]; then
    echo "Container not found, Creating contianer"
    # Create container
    docker run -it \
    -v ${VOLUME_HOST_PATH}:${VOLUME_CONTAINER_PATH}\
    -w ${VOLUME_CONTAINER_PATH} \
    --name ${CONTAINER_NAME} ${IMAGE_NAME} 
else
    echo "Container found ${FIND_CONTAINER}"
    # Start container
    docker start ${CONTAINER_NAME} 
    # attach to the container
    docker attach ${CONTAINER_NAME}
fi