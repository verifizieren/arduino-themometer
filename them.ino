#include <LiquidCrystal_PCF8574.h>  // Bibliothek LCD-Anzeige.
#include <DHT.h>
#define LM35 A2                     // Analoger Eingang mit 10-Bit AD-Wandler (Temperatursensor LM35).

#define DHTPIN D4 // Anschluss DHT11-Sensormodul.
#define DHTTYPE DHT11 // Typ DHT 11.


#define A 0x01
#define LED_bl D13
#define LED_rt D12
                      // Namen für die Zustände.
LiquidCrystal_PCF8574 lcd(0x27);    // LCD-Adresse auf 0x27 für 16 Zeichen und 2 Zeilen
DHT dht(DHTPIN, DHTTYPE); 
                                    // einschalten.
unsigned int Feuchte, Temperatur;
unsigned char zustand = 1;          // Zustandsvariable.
unsigned short z;                   // Digitaler Ausgang AD-Wandler (Zahlenwert z).
float temperatur;                   // Variable für die Temperatur.
void setup() {
  pinMode(LED_bl, OUTPUT);
  pinMode(LED_rt, OUTPUT);
  Serial.begin(115200);  //Seriellen Monitor initialisieren.
  I2C_LCD_init();        // LCD initialisieren.
  delay(500);
}

void loop() {
  switch (zustand) {
    case A:
      z = analogRead(LM35);
      temperatur = float(((z * 3.3)/1023)*100);
      Feuchte = dht.readHumidity();
      Temperatur = dht.readTemperature();

      if (temperatur >= 30){
        I2C_LCD("T = " + String(temperatur) + "C", "Humidity = " + String(Feuchte) + "%");
        blinker();
        delay(200);
      } else if (25 < temperatur < 30){
        I2C_LCD("T = " + String(temperatur) + "C", "Humidity = " + String(Feuchte) + "%");
        digitalWrite(LED_bl, 0);
        digitalWrite(LED_rt, 100);
        delay(500);
      }else if (20 < temperatur < 25){
        I2C_LCD("T = " + String(temperatur) + "C", "Humidity = " + String(Feuchte) + "%");
        digitalWrite(LED_bl, 100);
        digitalWrite(LED_rt, 100);
        delay(500);
      } else {
        I2C_LCD("T = " + String(temperatur) + "C", "Humidity = " + String(Feuchte) + "%");
        digitalWrite(LED_bl, 100);
        digitalWrite(LED_rt, 0);
        delay(500);
      }
      break;
  }
}

void blinker(){
  digitalWrite(LED_rt, 100);
  delay(10);
  digitalWrite(LED_rt, 0);
  delay(10);
}

  void I2C_LCD_init(void) {
    lcd.begin(16, 2);       // LCD initialisieren.
    lcd.clear();            // LCD löschen.
    lcd.setBacklight(255);  // Hintergrundlicht.
  }

  void I2C_LCD(String LCD_0, String LCD_1) {
    lcd.clear();          // LCD löschen
    lcd.setCursor(0, 0);  // Zeile 0 einstellen.
    lcd.print(LCD_0);     // Auf Zeile 0 ausgeben.
    lcd.setCursor(0, 1);  // Zeile 1 einstellen.
    lcd.print(LCD_1);     // Auf Zeile 1 ausgeben.
  }
