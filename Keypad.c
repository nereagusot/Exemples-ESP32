#include <Keypad.h>

#define LED_PIN 23   // LED conectado al GPIO 23

const byte ROWS = 4;
const byte COLS = 4;

// Mapa del teclado
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// TUS CONEXIONES (según tu imagen)
byte rowPins[ROWS] = {19, 18, 5, 17};   // Filas
byte colPins[COLS] = {16, 4, 2, 15};    // Columnas

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// PIN a validar
String pinCorrecto = "123";
String pinIngresado = "";

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("=== SISTEMA INICIADO ===");
  Serial.println("Ingrese PIN de 3 digitos:");
}

void parpadearLed(int tiempo_ms) {
  int ciclos = tiempo_ms / 400;  // 200ms ON + 200ms OFF

  for (int i = 0; i < ciclos; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Tecla: ");
    Serial.println(key);

    // Solo aceptar numeros
    if (key >= '0' && key <= '9') {
      pinIngresado += key;
      Serial.print("PIN actual: ");
      Serial.println(pinIngresado);
    }

    // Borrar con *
    if (key == '*') {
      pinIngresado = "";
      Serial.println("PIN borrado");
    }

    // Cuando hay 4 numeros → validar
    if (pinIngresado.length() == 3) {
      if (pinIngresado == pinCorrecto) {
        Serial.println("PIN CORRECTO - LED PARPADEANDO 5s");
        parpadearLed(5000);
      } 
      else {
        Serial.println("PIN INCORRECTO");
      }

      // Reiniciar para nuevo intento
      pinIngresado = "";
      Serial.println("\nIngrese PIN de 3 digitos:");
    }
  }
}
