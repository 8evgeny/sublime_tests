#! /usr/bin/bash
source /home/user/anaconda3/etc/profile.d/conda.sh
conda activate yolo5
rm -rf /home/user/yolov5/runs/train/*

python /home/user/yolov5/train.py --data night_fly.yaml --weights yolov5s.pt --img 512 --epochs 15  # from pretrained 

# from scratch
#python /home/user/yolov5/train.py --data /home/user/yolov5/data/coco128.yaml --weights '' --cfg yolov5s.yaml --img 640  --epochs 500 
# -m torch.distributed.run --nproc_per_node 4 --master_port 1 --device 0,1,2,3




#  Результаты обучения  /home/user/yolov5/runs/train/exp/weights/best.pt


# Проверка модели
python /home/user/yolov5/test2.py
