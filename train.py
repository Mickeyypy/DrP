from ultralytics import YOLO

model = YOLO("yolo11n.pt")

Train_results = model.train(
    data="datasets/data.yaml",
    epochs=100,
    imgsz=640,
    device="0",
    workers=0
)