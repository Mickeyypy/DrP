import cv2
import numpy as np

def process_image(image_path):
    # โหลดภาพ
    image = cv2.imread(image_path)
    if image is None:
        print("ไม่สามารถโหลดภาพได้ ตรวจสอบพาธไฟล์อีกครั้ง")
        return
    
    # แปลงเป็น Black and White (Binary)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    _, black_and_white = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
    
    # แปลงเป็น Gray Scale
    gray_image = gray.copy()
    
    # Half Black and White และ Half Color
    halfbw = image.copy()
    halfbw[:, :image.shape[1]//2] = cv2.cvtColor(gray[:, :image.shape[1]//2], cv2.COLOR_GRAY2BGR)
    
    # แสดงผลลัพธ์
    cv2.imshow('Original Image', image)
    cv2.imshow('Black and White', black_and_white)
    cv2.imshow('Gray Scale', gray_image)
    cv2.imshow('Half BW and Half Color', halfbw)
    
    cv2.waitKey(0)
    cv2.destroyAllWindows()

# เรียกใช้งานฟังก์ชันโดยใส่พาธภาพที่ต้องการ
process_image('Image/Screenshot_1.png')
