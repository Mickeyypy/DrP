int ledPin = 3; // ใช้ LED บนบอร์ด

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();  // อ่านค่าจาก Serial
    if (command == '1') {
      digitalWrite(ledPin, HIGH);  // เปิดไฟ LED ถ้าตรวจพบวัตถุ
      delay(500);
      digitalWrite(ledPin, LOW);   // ปิดไฟ LED
    }
  }
}
