#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WebServer.h>


ESP8266WebServer server(80);
String latestData = "";   // 网页显示的完整一组
String buffer = "";       // 正在累积的当前组
unsigned long lastRecvMs = 0;
unsigned long minDelayMs = 99999;
const char* ssid = "你的WiFi名";            // 你的WiFi
const char* password = "你的WiFi密码";
const char* mqtt_server = "bemfa.com";   // 巴法云MQTT服务器
const int   mqtt_port = 9501;
const char* uid = "你的巴法云UID";    // 改成你的巴法云UID
const char* topic = "esp001";            // 和主题名一致（大小写敏感）

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){   // 连不上就闪灯提示
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
  digitalWrite(LED_BUILTIN, LOW);   // 连上后常亮
  Serial.print("WiFi OK, IP: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.connect(uid, uid, uid);
  client.publish(topic, "esp8266 online");
  server.on("/", []() {
    unsigned long delayMs = millis() - lastRecvMs;   // 数据已接收多久
    if (delayMs < minDelayMs) minDelayMs = delayMs;
    String html = "<meta charset='utf-8'><meta http-equiv='refresh' content='3'>"
                  "<h2>环境数据</h2>"
                  "<p>当前延迟: " + String(delayMs) + " ms</p>"
                  "<p><b>最小延迟: " + String(minDelayMs) + " ms</b></p>"
                  "<pre>" + latestData + "</pre>";
    server.send(200, "text/html; charset=utf-8", html);
  });
  server.begin();
  Serial.print("网页地址: http://");
  Serial.println(WiFi.localIP());
}


void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    delay(3000);
    return;
  }
  client.loop();
  server.handleClient();
  if (!client.connected()) client.connect(uid, uid, uid);

  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) {
      buffer += line + "\n";          // 先累积这一行

      if (line.startsWith("=======")) { // 组结束标志：STM32 的最后一条分隔线
        latestData = buffer;          // 整组交给网页
        lastRecvMs = millis();
        client.publish(topic, buffer.c_str());   // 整组上云
        buffer = "";                  // 清空，等下一组
        Serial.println("--- 一组数据已转发 ---");
        unsigned long now = millis();
        static unsigned long lastGapMs = 0;
        if (lastGapMs != 0) {
          Serial.print("组间隔: ");
          Serial.println(now - lastGapMs);   // 正常应稳定在 1000 附近
        }
        lastGapMs = now;
      }
    }
  }
}