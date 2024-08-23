#! /usr/bin/bash
source /home/user/anaconda3/etc/profile.d/conda.sh
conda activate yolo5

python /home/user/yolov5/export.py --weights "/home/user/yolov5/runs/train/exp/weights/best.pt" --include onnx
conda activate fastdeploy
rm -rf /home/user/rknpu2/examples/rknn_yolov5_demo/convert_rknn_demo/yolov5/rknn_models/*
#rm /home/user/rknpu2/examples/rknn_yolov5_demo/convert_rknn_demo/yolov5/onnx_models/best.onnx
#cp /home/user/yolov5/runs/train/exp/weights/best.onnx /home/user/rknpu2/examples/rknn_yolov5_demo/convert_rknn_demo/yolov5/onnx_models/
python3 /home/user/rknpu2/examples/rknn_yolov5_demo/convert_rknn_demo/yolov5/onnx2rknn.py 
