#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>

const char* ssid = "Your_WiFi_Name";        // Wi-Fi 名称
const char* password = "Your_WiFi_Password"; // Wi-Fi 密码

Servo myServo;
const int servoPin = 5; 
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi!");

  myServo.attach(servoPin);
  myServo.write(0); // 初始位置

  // HTTP 控制接口
  server.on("/turn_off", HTTP_GET, [](AsyncWebServerRequest *request){
    myServo.write(90);  // 推动开关
    delay(1000);        // 停留
    myServo.write(0);   // 复位
    request->send(200, "text/plain", "Turned off!");
  });

  server.begin();
}

void loop() {}
