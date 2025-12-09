#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>  // Necesitas instalar esta librería desde el Library Manager

const char* ssid = "AP_asix";
const char* password = "AP_asix2023";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://worldtimeapi.org/api/timezone/Europe/London");
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();

      // Parseamos el JSON
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        const char* datetime = doc["datetime"]; // Ejemplo: "2025-12-09T18:45:30.123456+00:00"
        
        // Separar fecha y hora
        String date = String(datetime).substring(0, 10); // "2025-12-09"
        String time = String(datetime).substring(11, 19); // "18:45:30"
        
        Serial.print("Fecha: ");
        Serial.println(date);
        Serial.print("Hora: ");
        Serial.println(time);
      } else {
        Serial.println("Error parseando JSON");
      }
    } else {
      Serial.println("Error en la petición HTTP");
    }

    http.end();
  }

  delay(5000); // Espera 5 segundos antes de la siguiente petición
}
