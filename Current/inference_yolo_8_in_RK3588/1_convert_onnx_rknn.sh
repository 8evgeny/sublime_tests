#!/bin/bash

source /home/user/anaconda3/etc/profile.d/conda.sh
conda activate fastdeploy
python examples/yolov8/python/convert.py best.onnx rk3588




#`<onnx_model>`: Specify ONNX model path.
#`<TARGET_PLATFORM>`: Specify NPU platform name. Such as 'rk3588'.
#`<dtype>(optional)`: Specify as `i8`, `u8` or `fp`. `i8`/`u8` for doing quantization, `fp` for no quantization. Default is `i8`.
#`<output_rknn_path>(optional)`: Specify save path for the RKNN model, default save in the same directory as ONNX model with name `yolov8.rknn`
