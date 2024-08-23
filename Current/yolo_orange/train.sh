#! /usr/bin/bash
source /home/user/anaconda3/etc/profile.d/conda.sh
conda activate yolo5
rm -rf /home/user/yolov5/runs/train/*
python /home/user/yolov5/train.py --img 640 --epochs 1 --data coco128.yaml --weights yolov5s.pt

#  Результаты обучения  /home/user/yolov5/runs/train/exp/weights/best.pt


# Проверка модели
