#include <WiFi.h>
#include <WebServer.h>

// กำหนดขาเชื่อมต่อกับ L298N
#define IN1 14  // มอเตอร์ซ้ายไปหน้า
#define IN2 15  // มอเตอร์ซ้ายไปหลัง
#define IN3 12  // มอเตอร์ขวาไปหน้า
#define IN4 13  // มอเตอร์ขวาไปหลัง

// WiFi Credentials
const char* ssid = "Razorbladz";  // ตั้งค่า WiFi ของคุณ
const char* password = "00000000";

WebServer server(80);  // กำหนด Web Server ที่พอร์ต 80

// ฟังก์ชันควบคุมรถ
void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void moveBackward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void turnLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stopCar() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

// HTML Interface สำหรับควบคุมรถ
void handleRoot() {
    server.send(200, "text/html", R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
            <title>ESP32-CAM Car</title>
            <style>
                body { font-family: Arial; text-align: center; margin-top: 50px; }
                button { font-size: 20px; padding: 10px; margin: 5px; width: 100px; }
            </style>
            <script>
                function sendCommand(command) {
                    var xhttp = new XMLHttpRequest();
                    xhttp.open("GET", command, true);
                    xhttp.send();
                }
            </script>
        </head>
        <body>
            <h1>ESP32-CAM Car Control</h1>
            <button onmousedown="sendCommand('forward')" onmouseup="sendCommand('stop')">Forward</button><br>
            <button onmousedown="sendCommand('left')" onmouseup="sendCommand('stop')">Left</button>
            <button onmousedown="sendCommand('right')" onmouseup="sendCommand('stop')">Right</button><br>
            <button onmousedown="sendCommand('backward')" onmouseup="sendCommand('stop')">Backward</button>
        </body>
        </html>
    )rawliteral");
}

// ฟังก์ชันสำหรับรับคำสั่งจาก Web
void handleForward() { moveForward(); server.send(200, "text/plain", "Moving Forward"); }
void handleBackward() { moveBackward(); server.send(200, "text/plain", "Moving Backward"); }
void handleLeft() { turnLeft(); server.send(200, "text/plain", "Turning Left"); }
void handleRight() { turnRight(); server.send(200, "text/plain", "Turning Right"); }
void handleStop() { stopCar(); server.send(200, "text/plain", "Stopped"); }

void setup() {
    Serial.begin(115200);

    // กำหนดโหมดขาเป็น OUTPUT
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    stopCar();  // เริ่มต้นให้รถหยุด

    // เชื่อมต่อ WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // ตั้งค่า Web Server
    server.on("/", handleRoot);
    server.on("/forward", handleForward);
    server.on("/backward", handleBackward);
    server.on("/left", handleLeft);
    server.on("/right", handleRight);
    server.on("/stop", handleStop);

    server.begin();
}

void loop() {
    server.handleClient();
}
