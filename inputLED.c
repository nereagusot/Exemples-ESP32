/*
  Project: Blink (El "Hello, World!" dels microcontroladors)
  Description: Fa parpellejar un LED connectat al pin 23.
*/

// Definim una constant per al pin on hem connectat el LED
const int LED_PIN = 23;
int encendido = 0;
int apagado = 0;

// La funció setup() s'executa un cop quan la placa arrenca
void setup() {
  // Configurem el pin del LED com una SORTIDA (OUTPUT)
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Dime el tiempo de encendido: de 1000 a 5000");
  while (encendido == 0) { // espera hasta que el usuario escriba algo
    if (Serial.available() > 0) {
      encendido = Serial.parseInt();
    }
  }
  

  Serial.println("Dime el tiempo de apagado: de 1000 a 5000");
  while (apagado == 0) { // espera hasta que el usuario escriba algo
    if (Serial.available() > 0) {
      apagado = Serial.parseInt();
    }
  }
 


}

// La funció loop() s'executa contínuament
void loop() {
  
  digitalWrite(LED_PIN, HIGH);  // Envia 3.3V al pin (encén el LED)
  delay(encendido);                  // Espera 1000 mil·lisegons (1 segon)
  
  digitalWrite(LED_PIN, LOW);   // Envia 0V al pin (apaga el LED)
  delay(apagado);                  // Espera 1 segon
}
