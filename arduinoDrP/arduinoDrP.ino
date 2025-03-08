#include WebServer.h
#include WiFi.h
#include esp32cam.h

const char WIFI_SSID = Razorbladz;
const char WIFI_PASS = 00000000;
const char URL = cam.jpg;

static auto RES = esp32camResolutionfind(800, 600);

WebServer server(80);

void serveJpg() {
  auto frame = esp32camcapture();
  if (frame == nullptr) {
    Serial.println(CAPTURE FAILED!);
    server.send(503, , );
    return;
  }
  Serial.printf(CAPTURE OK %dx%d %dbn,
                frame-getWidth(), frame-getHeight(),
                static_castint(frame-size()));

  server.setContentLength(frame-size());
  server.send(200, imagejpeg);

  WiFiClient client = server.client();
  frame-writeTo(client);
}

void handleJpg() {
  if (!esp32camCamera.changeResolution(RES)) {
    Serial.println(CAN'T SET RESOLUTION!);
  }
  serveJpg();
}

void initCamera() {
  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pinsAiThinker);
    cfg.setResolution(RES);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);

    bool ok = Camera.begin(cfg);
    Serial.println(ok  CAMERA OK  CAMERA FAIL);
  }
}

void initWifi() {
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
    ;
  Serial.printf(http%s%sn,
                WiFi.localIP().toString().c_str(), URL);
}

void initServer() {
  server.on(URL, handleJpg);
  server.begin();
}

void setup() {
  Serial.begin(115200);
  initWifi();
  initCamera();
  initServer();
}

void loop() {
  server.handleClient();
}