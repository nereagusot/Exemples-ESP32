#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PubSubClient.h> // Librería MQTT

LiquidCrystal_I2C LCD(0x27, 16, 2);

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqttServer = "test.mosquitto.org"; // Broker público
const int mqttPort = 1883;
const char* mqttTopic = "wokwi/esp32/lcd";

WiFiClient espClient;
PubSubClient client(espClient);

// Spinner para mostrar conexión
void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdb";
  LCD.setCursor(15, 1);
  LCD.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) counter = 0;
}

// Callback MQTT: se llama cuando llega un mensaje
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("MQTT Message:");
  LCD.setCursor(0,1);
  LCD.print(msg);
}

void setupWiFi() {
  WiFi.begin(ssid, password);
  LCD.setCursor(0, 0);
  LCD.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    spinner();
  }
  LCD.clear();
  LCD.setCursor(0,0);
  LCD.print("WiFi Connected");
  Serial.println("WiFi connected");
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe(mqttTopic); // Suscribirse al topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  LCD.init();
  LCD.backlight();

  setupWiFi();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop(); // Mantiene la conexión y procesa mensajes
}
