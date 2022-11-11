// C++ code
//
int distanceThreshold = 0;

int cm = 0;

int inches = 0;

#include <Adafruit_LiquidCrystal.h>

int seconds = 0;

Adafruit_LiquidCrystal lcd_1(0);

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  lcd_1.begin(16, 2);
  lcd_1.print("Vagas livres:");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Vagas Ocupadas:");
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  // set threshold distance to activate LEDs
  distanceThreshold = 350;
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7, 6);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(cm);
  Serial.print("cm, ");
  Serial.print(inches);
  Serial.println("in");
  if (cm > distanceThreshold) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
  }
  if (cm <= distanceThreshold && cm > distanceThreshold - 100) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    lcd_1.setCursor(15, 0);
  	lcd_1.print(1);
    lcd_1.setCursor(15, 1);
  	lcd_1.print(0);
  }
  if (cm <= distanceThreshold - 100 && cm > distanceThreshold - 250) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    lcd_1.setCursor(15, 0);
  	lcd_1.print(0);
    lcd_1.setCursor(15, 1);
  	lcd_1.print(1);
    
  }
  if (cm <= distanceThreshold - 250 && cm > distanceThreshold - 350) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    lcd_1.setCursor(15, 0);
  	lcd_1.print(0);
    lcd_1.setCursor(15, 1);
  	lcd_1.print(1);
  }
  if (cm <= distanceThreshold - 350) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    lcd_1.setCursor(15, 0);
  	lcd_1.print(0);
    lcd_1.setCursor(15, 1);
  	lcd_1.print(1);
  }
  delay(100); // Wait for 100 millisecond(s)
}
