#!/bin/bash
gcc basic-tutorial-4.c -o Release/basic-tutorial-4 `pkg-config --cflags --libs gstreamer-1.0`
