docker build  --progress=plain -t <img_name> .
docker container run -it --rm -e GOOGLE_APPLICATION_CREDENTIALS=/tmp/key.json  <img_name> bash
