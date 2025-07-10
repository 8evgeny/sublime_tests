#!/bin/bash
gcc basic-tutorial-3.c -o Release/basic-tutorial-3 `pkg-config --cflags --libs gstreamer-1.0`
