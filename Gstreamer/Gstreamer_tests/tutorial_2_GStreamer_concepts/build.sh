#!/bin/bash
gcc basic-tutorial-2.c -o Release/basic-tutorial-2 `pkg-config --cflags --libs gstreamer-1.0`
