#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Definitions
const int sensor_pin = A0;
const int relay_pin = 7;

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(sensor_pin, INPUT);
  pinMode(relay_pin, OUTPUT);

  // Relay OFF initially (for Active LOW relay)
  digitalWrite(relay_pin, HIGH);

  // Welcome Screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART");
  lcd.setCursor(0, 1);
  lcd.print("IRRIGATION SYS  ");
  delay(6000);

  
  lcd.clear();
}

void loop()
{
  int sensor_data = analogRead(sensor_pin);

  // Convert sensor reading to moisture percentage
  int moisturePercent = map(sensor_data, 1023, 0, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Sensor Value : ");
  Serial.print(sensor_data);

  Serial.print("   Moisture : ");
  Serial.print(moisturePercent);
  Serial.println("%");

  lcd.clear();

  // Soil Dry
  if (sensor_data > 950)
  {
    digitalWrite(relay_pin, LOW);   // Pump ON (Active LOW relay)

    lcd.setCursor(0, 0);
    lcd.print("SOIL DRY");

    lcd.setCursor(0, 1);
    lcd.print("M:");
    lcd.print(moisturePercent);
    lcd.print("% P:ON");

    Serial.println("Pump ON");
  }

  // Medium Moisture
  else if (sensor_data >= 400 && sensor_data <= 950)
  {
    digitalWrite(relay_pin, HIGH);   // Pump OFF

    lcd.setCursor(0, 0);
    lcd.print("SOIL MEDIUM");

    lcd.setCursor(0, 1);
    lcd.print("M:");
    lcd.print(moisturePercent);
    lcd.print("% P:OFF");

    Serial.println("Pump OFF");
  }

  // Soil Wet
  else
  {
    digitalWrite(relay_pin, HIGH);   // Pump OFF

    lcd.setCursor(0, 0);
    lcd.print("SOIL WET");

    lcd.setCursor(0, 1);
    lcd.print("M:");
    lcd.print(moisturePercent);
    lcd.print("% P:OFF");

    Serial.println("Pump OFF");
  }

  delay(1000);
}