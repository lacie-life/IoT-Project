#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "MPH"; // Enter your WiFi name
const char* password =  "mph.vn2019"; // Enter WiFi password
const char* mqttServer = "54.255.103.68";
const int mqttPort = 1883;
// const char* mqttUser = "otfxknod";
// const char* mqttPassword = "nSuUc1dDLygF";

WiFiClient espClient;
PubSubClient client(espClient);

char msg[50];
volatile long time_;
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.println(F(" Address IP of ESP8266: "));
  Serial.println(WiFi.localIP());  // WiFi.localIP() - return address IP of ESP8266.
  //--------------------- End connect with Wifi ----------------
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("NodeMCU")) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
}

void Json(String temperature,String humidity,String brightness)
 {
  String temp = "{";
  temp += "\"temperature\":";
  temp += temperature;
  temp += ",";
  temp += "\"humidity\":";
  temp += humidity;
  temp += ",";
  temp += "\"brightness\":";
  temp += brightness;
  temp += "}";
  Serial.println(temp);
  snprintf (msg, 75, temp.c_str());
  client.publish("garden1/sensor1", msg);
 }

void sensor()
 {
    int h = random(40, 90); 
    int t = random(20, 40);
    int val = random(10, 90);
    if ((unsigned long) (millis() - time_) > 10000 ){         
        Serial.println();
        time_ = millis();
        Serial.print ("nhiet do: ");
        Serial.println (t);                                 
        Serial.print("do am: ");
        Serial.println (h);                                 
        Serial.print ("anh sang: ");
        Serial.println (val);
 
        Json(String(t), String(h),String(val));
    }
 }
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");

}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("garden1/mode1");
      client.subscribe("garden1/refresh1");
      client.subscribe("garden1/light1");
      client.subscribe("garden1/pump1");
      client.subscribe("garden1/parameter1");
      client.subscribe("garden1/fan1");
    } else {
      client.state();
      delay(5000);
    }
  }
}
 
void loop() {
  // Kiểm tra kết nối
  if (!client.connected()) {
    reconnect();
  }
  
  sensor();
  client.loop();
}
