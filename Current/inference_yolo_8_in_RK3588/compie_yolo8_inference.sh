#!/bin/bash


rm -rf build/*
rm -rf install/*
# yolov8 - это папка в examples
./build-linux.sh -t rk3588 -a aarch64 -d yolov8
