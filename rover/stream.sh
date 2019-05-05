#!/bin/sh

PORT="8080"
ID="rover"
PW="1234"
SIZE="320x240"
FRAMERATE="30"

export LD_LIBRARY_PATH=/usr/local/lib
mjpg_streamer -i "input_uvc.so -f $FRAMERATE -r $SIZE -d /dev/video0 -y" -o "output_http.so -w /var/www/html -p $PORT"