#! /bin/bash

mkdir -p output/dl
curl -L -o output/dl/dl.json https://api.github.com/repos/paulshir/Model01-Firmware/releases/latest
HEX_FILE_URL=$(cat ./output/dl/dl.json | jq ".assets[] | .browser_download_url" | grep ".hex" | sed s/\"//g)
HEX_FILE_PATH=./output/dl/$(cat output/dl/dl.json | jq ".assets[] | .name" | grep ".hex" | sed s/\"//g)
echo $HEX_FILE_URL
echo $HEX_FILE_PATH
curl -L -o $HEX_FILE_PATH $HEX_FILE_URL
make flash HEX_FILE_PATH=$HEX_FILE_PATH
