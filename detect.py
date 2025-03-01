import cv2
import serial  # ใช้สื่อสารกับ Arduino
import time
from ultralytics import YOLO

# เปิดการเชื่อมต่อกับ Arduino (เปลี่ยนพอร์ตตามอุปกรณ์ของคุณ เช่น 'COM3' หรือ '/dev/ttyUSB0')
arduino = serial.Serial(port='COM6', baudrate=115200, timeout=1)
time.sleep(2)  # รอให้ Arduino พร้อม

# โหลดโมเดล YOLO
model = YOLO("yolo11n.pt")

# เปิดกล้อง
cap = cv2.VideoCapture(0)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    # รัน YOLO
    results = model(frame)

    # แสดงผลลัพธ์
    annotated_frame = results[0].plot()
    cv2.imshow("YOLO Detection", annotated_frame)

    # ตรวจจับวัตถุ (เช่น "cup") แล้วส่งคำสั่งไป Arduino
    for obj in results[0].boxes.cls:
        class_name = model.names[int(obj)]  # ชื่อคลาสของวัตถุ
        if class_name == "cup":
            arduino.write(b'1')  # ส่ง '1' ไปให้ Arduino
            print("Cup detected! Sending signal to Arduino")

    # กด 'q' เพื่อออก
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# ปิดการเชื่อมต่อ
cap.release()
cv2.destroyAllWindows()
arduino.close()