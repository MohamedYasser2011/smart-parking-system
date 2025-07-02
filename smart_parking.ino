#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Gate Ultrasonic sensor pins
const int trigPin = A2;
const int echoPin = A3;

// Parking slot sensor pins
const int trigPins[3] = {2, 4, 6};
const int echoPins[3] = {3, 5, 7};

// LED pins
const int greenLEDs[3] = {8, 10, 12};
const int redLEDs[3] = {A0, 11, 13};

// Servo motor pin
const int servoPin = 9;

// LCD setup: address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo parameters
const int closedAngle = 90;
const int openAngle = 0;

// Detection thresholds
const int detectionDistance = 30;     // cm for gate
const int slotDetectionDistance = 15; // cm for parking slot detection

Servo gateServo;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Parking System");

  // Setup gate ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Setup parking ultrasonic
  for (int i = 0; i < 3; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }

  // Setup LEDs
  for (int i = 0; i < 3; i++) {
    pinMode(greenLEDs[i], OUTPUT);
    pinMode(redLEDs[i], OUTPUT);
    digitalWrite(greenLEDs[i], LOW);
    digitalWrite(redLEDs[i], LOW);
  }

  gateServo.attach(servoPin);
  gateServo.write(closedAngle);

  Serial.begin(9600);
  delay(2000);
}

void loop() {
  bool allSlotsFull = true;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("S1:  S2:  S3:");
  lcd.setCursor(0, 1);

  for (int i = 0; i < 3; i++) {
    long slotDistance = measureDistance(trigPins[i], echoPins[i]);
    Serial.print("Slot ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(slotDistance);
    Serial.println(" cm");

    if (slotDistance < slotDetectionDistance && slotDistance > 0) {
      digitalWrite(greenLEDs[i], LOW);
      digitalWrite(redLEDs[i], HIGH);
      lcd.setCursor(i * 5, 1);
      lcd.print("Full ");
    } else {
      digitalWrite(greenLEDs[i], HIGH);
      digitalWrite(redLEDs[i], LOW);
      lcd.setCursor(i * 5, 1);
      lcd.print("Free ");
      allSlotsFull = false;
    }
  }

  // Gate sensor
  long gateDistance = measureDistance(trigPin, echoPin);
  Serial.print("Gate Distance: ");
  Serial.println(gateDistance);

  if (gateDistance > 0 && gateDistance < detectionDistance) {
    if (allSlotsFull) {
      Serial.println("Parking Full - Gate will not open");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Parking is FULL");
      lcd.setCursor(0, 1);
      lcd.print("Please Wait...");
      delay(2000);
    } else {
      Serial.println("Object detected - opening gate");
      openGate();

      // Wait in 30 second intervals as long as object remains
      while (true) {
        unsigned long waitStart = millis();
        while (millis() - waitStart < 10000) {
          delay(100); // Check every 100ms
        }

        long currentDistance = measureDistance(trigPin, echoPin);
        Serial.print("After 30s check: ");
        Serial.println(currentDistance);

        if (currentDistance > detectionDistance || currentDistance == -1) {
          break;
        } else {
          Serial.println("Still detected - extending gate open time");
        }
      }

      Serial.println("Closing gate");
      closeGate();
      delay(1000);
    }
  }

  delay(500);
}

// Generic distance measurement
long measureDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000); // 30ms timeout
  if (duration == 0) return -1; // No echo received

  return duration * 0.034 / 2;
}

void openGate() {
  gateServo.write(openAngle);
}

void closeGate() {
  gateServo.write(closedAngle);
}
