#include <stdio.h>
#include <stdbool.h> 

void setup() {
  Serial.begin(115200);

  // Variable de tipo int: números enteros
  int edad = 16;
  Serial.print("Edad (int): ");
  Serial.println(edad);

  // Variable de tipo float: números con decimales
  float temperatura = 23.5;
  Serial.print("Temperatura (float): ");
  Serial.println(temperatura);

  // Variable de tipo char: un solo carácter
  char inicial = 'A';
  Serial.print("Inicial (char): ");
  Serial.println(inicial);

  // Cadena de texto en C: se usa un array de char
  char nombre[] = "Juan";
  Serial.print("Nombre (char[]): ");
  Serial.println(nombre);

  // Variable booleana verdadero o falso.
  bool aprobado = true;
  Serial.print("Aprobado (bool): ");
  Serial.println(aprobado);

  // Constante: no cambia nunca
  const int MAX_PUNTOS = 100;
  Serial.print("Máx puntos (const int): ");
  Serial.println(MAX_PUNTOS);

  Serial.println("\n¡Fin del ejemplo!");
}

void loop() {
  // Vacío para que se imprima una vez sólo
}