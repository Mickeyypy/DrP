# สวัสดีเพื่อนๆอันนี้เป็น Github project ที่กูสร้างขึ้นมา
## ไฟล์ประกอบด้วย datasets, test, detect.py อันอื่นๆไม่ต้องสนใจ
datasets คือไฟล์ที่เอาไว้เทรนmodel (ยังไม่ได้ใช้)

detect.py คือโค้ดที่ Object detection ของเรา (Python)

yolo11n.pt คือโมเดล Object detection model พัฒนาโดย Ultralytics เหมือนมันจะสามารถไปเทรนต่อให้มันตรวจจับเฉพาะวัตถุที่เราต้องการได้

arduinoDrP ต้องUpload เข้าบอร์ด Arduino Uno ก่อน ตอนนี้ยังไม่ได้โค้ดให้มันใช้กับบอร์ดESP32 เพราะทำไม่เป็น