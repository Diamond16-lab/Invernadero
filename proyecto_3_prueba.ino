/ Librerías necesarias
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Stepper.h>
#include <DHT.h>

// Declaración de objetos
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Objeto para la pantalla LCD
Servo Servomotor; // Objeto para el servomotor
Stepper myStepper(stepsPerRevolution, 38, 40, 39, 41); // Objeto para el motor paso a paso
DHT dht(DHT11_PIN, DHTTYPE); // Objeto para el sensor de humedad y temperatura DHT11

// Definición de constantes y variables
const int pot = A2; // Pin analógico para el potenciómetro
const int ventilador = 13; // Pin digital para el ventilador
const int ftr = A0; // Pin analógico para la fotoresistencia
const int Temperatura = A1; // Pin analógico para el sensor de temperatura LM35
const int HumedadPin = A4; // Pin analógico para el sensor de humedad del suelo
const int inPin = 0; // Pin analógico para el control de la bomba de agua
const int stepsPerRevolution = 2038; // Número de pasos por revolución del motor paso a paso
const int vueltas = 6; // Número de vueltas que necesita la polea
double luz; // Valor de la fotoresistencia calibrado
float lm35Calibracion = -15; // Ajuste para el sensor LM35 (en grados Celsius)
int fotoresistenciaCalibracion = -2; // Ajuste para la fotoresistencia
int sensorHS = 0; // Valor del sensor de humedad del suelo
int sensorMin = 1023; // Valor mínimo del sensor de humedad del suelo
int sensorMax = 0; // Valor máximo del sensor de humedad del suelo
bool abierto; // Estado de la polea


void setup() {
// Inicializar objetos
  lcd.begin(16, 2);   // Inicializa el objeto "lcd" indicando que se va a utilizar una pantalla de 16x2 caracteres.
  Serial.begin(9600);   // Inicializa la comunicación serial a una velocidad de 9600 baudios.
  pinMode(ventilador, OUTPUT);   // Configura el pin del ventilador como salida.
  Servomotor.attach(9);   // Inicializa el objeto "Servomotor" de la librería Servo y se le indica que va a ser controlado a través del pin 9.
  DHT.begin();   // Inicializa el objeto "DHT" de la librería DHT, que permite leer la información del sensor de humedad y temperatura.
  pinMode(HumedadPin, INPUT);   // Configura el pin del sensor de humedad del suelo como entrada.
}

void loop() {
// Leer valores del potenciómetro, sensor de temperatura y fotresistencia
      
   //Potenciometro----------
      int potenciometro  = analogRead(pot);
      float voltaje = potenciometro * (5.0 / 1023.0);
      Serial.print("voltaje:   \n" );
      //-----------------------
      
//Calculo De Temperatura A Centigrados

   // Lectura del sensor de temperatura LM35
    int lm35Value = analogRead(Temperatura);
    float millivolts = (lm35Value / 1023.0) * 5000;
    float celsius = (millivolts / 10) + lm35Calibracion; // Aplicar la calibración
    Serial.print("Temperatura: C");
    Serial.print(celsius);
    
    // Lectura del sensor de fotoresistencia
    int fotoresistenciaValue = analogRead(ftr);
    luz = (double)(fotoresistenciaValue / 9.74) - fotoresistenciaCalibracion; // aplicar doble calibración
    Serial.print(" \n Valor de la fotoresistencia: ");
    Serial.print(luz);
    
    // Control del servo basado en la temperatura
    if (celsius > 34) {
    Servomotor.write(90); // Activar servo
    digitalWrite(ventilador, HIGH); // Encender ventilador
    Serial.println("El ventilador se activó: ");
    Serial.print(ventilador);
    if (!abierto){
    myStepper.setSpeed(vueltas);
    myStepper.step(stepsPerRevolution);
    }
    abierto = true;
    lcd.setCursor(11,1);
    lcd.print("Open ");
    } else {
    myservo.write(0); // Desactivar servo
    digitalWrite(ventilador, LOW); // Apagar ventilador
    Serial.println("El ventilador se desactivó: ");
    Serial.print(ventilador);
    if (abierto){
    myStepper.setSpeed(vueltas);
    myStepper.step(-stepsPerRevolution);
    }
    abierto = false;
    lcd.setCursor(11,1);
    lcd.print("Close");
    }
    
    // Lectura del sensor de humedad y temperatura DHT11
    int chk = DHT.read(DHT11_PIN);
    //***********
    
    // Sensor de humedad del suelo
    sensorValue=analogRead(HumedadPin); // Leemos el valor del sensor
    
    // Si el valor leído es menor que el valor mínimo actual, lo actualizamos
    if (sensorValue < sensorMin) {
    sensorMin = sensorValue;
    }
    // Si el valor leído es mayor que el valor máximo actual, lo actualizamos
    if (sensorValue > sensorMax) {
    sensorMax = sensorValue;
    }

    // Calculamos el rango del sensor (diferencia entre el valor máximo y mínimo)
      int sensorRange = sensorMax - sensorMin;
      
    // Mapeamos el valor actual del sensor al rango de 0-100%
      int mappedValue = map(sensorValue, sensorMin, sensorMax, 0, 100);
      
    // Imprimimos el valor actual del sensor, el valor mínimo, el valor máximo y el rango actual
      Serial.print("Valor actual del sensor: ");
      Serial.print(sensorValue);
      Serial.print(" | Valor mínimo: ");
      Serial.print(sensorMin);
      Serial.print(" | Valor máximo: ");
      Serial.print(sensorMax);
      Serial.print(" | Rango actual: ");
      Serial.print(sensorRange);
      Serial.print("\n");
      
    // Imprimimos el valor actual del sensor mapeado al rango de 0-100%
      Serial.print("Valor mapeado: ");
      Serial.print(mappedValue);
      Serial.println("%");
      
      delay(1000); // Esperamos un segundo antes de volver a leer el sensor
      
    // Actualizar pantalla
      lcd.setCursor(0, 0);
      lcd.print("TempLM35: ");
      lcd.print(celsius);
      lcd.print(" C ");
      
      lcd.setCursor(0, 1);
      lcd.print("Luz: ");
      lcd.print(luz);
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Temp: ");
      lcd.print(DHT.temperature);
      lcd.print(" C");
      lcd.setCursor(0,1);
      lcd.print("Hum: ");
      lcd.print(DHT.humidity);
      lcd.print(" %");
      delay(2000);
      
    // Esperar un breve periodo de tiempo antes de repetir el ciclo
      delay(1000);
      
      Serial.print(analogRead(A0));
      Serial.print("\n");
      delay(800);

}
      
