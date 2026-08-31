#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
// --- DHT ---
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// --- LCD ---
LiquidCrystal_I2C lcd(0x27, 16, 2);
// --- LED ---
int ledPin = 11;
float tempThreshold = 25.0;
// --- KEYPAD ---
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {3, 4, 5, 6};
byte colPins[COLS] = {7, 8, 9, 10};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
// --- VARIJABLE ---
String input = "";
bool settingMode = false;
void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(ledPin, OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("Meteo stanica");
  delay(2000);
  lcd.clear();
}
void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  char key = keypad.getKey();
  if (key) {
    handleKey(key);
  }
  if (!settingMode) {
    displayData(temp, hum);
  }
  checkLED(temp);
  delay(1000);
}
// --- FUNKCIJE ---
void displayData(float temp, float hum) {
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C ");
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(hum);
  lcd.print("% ");
}
void checkLED(float temp) {
  if (temp >= tempThreshold) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}

void handleKey(char key) {
  if (key == '#') {
    settingMode = true;
    input = "";
    lcd.clear();
    lcd.print("Postavi temp:");
  }
  else if (settingMode) {
    if (key >= '0' && key <= '9') {
      input += key;
      lcd.setCursor(0,1);
      lcd.print(input);
    }
    else if (key == '*') {
      tempThreshold = input.toFloat();
      settingMode = false;
      lcd.clear();
      lcd.print("Spremljeno!");
      delay(1500);
      lcd.clear();
    }
  }
}
