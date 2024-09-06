#!/bin/bash


rm -rf build/*
rm -rf install/*

./build-linux.sh -t rk3588 -a aarch64 -d yolov8_coco
