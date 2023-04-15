#include <dht.h>
#include <LiquidCrystal.h>

dht DHT;
#define DHT11_PIN 7 // Pin digital al que está conectado el sensor DHT11
#define HIGROMETRO_PIN A0 // Pin analógico al que está conectado el sensor higrómetro
#define LM35_PIN A1 // Pin analógico al que está conectado el sensor LM35
#define RELE_BOMBA 2 // Pin digital al que está conectado el relé de la bomba de agua
#define RELE_VENTILADOR 3 // Pin digital al que está conectado el relé del ventilador

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Configurar los pines para el display LCD

void setup() {
  Serial.begin(9600);
  pinMode(RELE_BOMBA, OUTPUT);
  pinMode(RELE_VENTILADOR, OUTPUT);
  lcd.begin(16, 2); // Inicializar el display LCD
  lcd.print("Temperatura:"); // Imprimir la etiqueta de temperatura en la primera fila del display LCD
  lcd.setCursor(0, 1); // Mover el cursor del display LCD a la segunda fila
  lcd.print("Humedad:"); // Imprimir la etiqueta de humedad en la segunda fila del display LCD
}

void loop() {
  int higrometro = analogRead(HIGROMETRO_PIN); // Leer la lectura analógica del sensor higrómetro
  int lm35_raw = analogRead(LM35_PIN); // Leer la lectura analógica del sensor LM35
  float lm35 = (lm35_raw * 5.0) / 1024.0; // Convertir la lectura analógica del sensor LM35 en grados Celsius
  int chk = DHT.read11(DHT11_PIN); // Leer la lectura digital del sensor DHT11

  if (chk == DHTLIB_OK) { // Si la lectura digital del sensor DHT11 es correcta
    float temp_dht11 = DHT.temperature; // Obtener la temperatura del sensor DHT11 en grados Celsius
    float hum_dht11 = DHT.humidity; // Obtener la humedad del sensor DHT11 en porcentaje

    Serial.print("Temperatura DHT11: ");
    Serial.print(temp_dht11);
    Serial.print("C, Humedad DHT11: ");
    Serial.print(hum_dht11);
    Serial.print("%, Temperatura LM35: ");
    Serial.print(lm35);
    Serial.println("C");

    // Actualizar los valores de temperatura y humedad en el display LCD
    lcd.setCursor(13, 0);
    lcd.print(temp_dht11);
    lcd.setCursor(8, 1);
    lcd.print(hum_dht11);

    if (temp_dht11 > 25 && hum_dht11 > 50) { // Si la temperatura es mayor a 25°C y la humedad es mayor a 50%
      digitalWrite(RELE_BOMBA, HIGH); // Activar el relé de la bomba de agua
      digitalWrite(RELE_VENTILADOR, HIGH); // Activar el relé del ventilador
    } else {
      digitalWrite(RELE_BOMBA, LOW); // Desactivar el relé de la bomba de agua
      digitalWrite(RELE_VENTILADOR, LOW); // Desactivar el relé del ventilador
}
} else { // Si la lectura digital del sensor DHT11 no es correcta
Serial.print("Error en la lectura del sensor DHT11: ");
Serial.println(DHT.read11(DHT11_PIN));
}

delay(2000); // Esperar 2 segundos antes de leer nuevamente los sensores
}
