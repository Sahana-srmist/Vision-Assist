#include <LiquidCrystal.h>

// Define LCD pins (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define Ultrasonic Sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Define Buzzer and Vibrator pins
const int buzzer = 7;
const int vibrator = 6;

// Variable for distance measurement
long duration;
int distance;

void setup() {
    // Set pin modes
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(vibrator, OUTPUT);

    // Initialize LCD
    lcd.begin(16, 2);
    lcd.print("VISION ASSIST!");
    delay(1000);
    lcd.clear();
}

void loop() {
    // Trigger Ultrasonic Sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read Echo response
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;  // Convert time to distance (cm)

    // Display distance on LCD
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm   "); // Extra spaces to clear old data

    // Alert Mechanism
    if (distance > 0 && distance < 50) { // Less than 50 cm
        digitalWrite(buzzer, HIGH);  // Turn ON buzzer
        digitalWrite(vibrator, HIGH); // Turn ON vibrator
        lcd.setCursor(0, 1);
        lcd.print("Alert! Obstacle ");
    } else { // 50 cm or more
        digitalWrite(buzzer, LOW);   // Turn OFF buzzer
        digitalWrite(vibrator, LOW); // Turn OFF vibrator
        lcd.setCursor(0, 1);
        lcd.print("Clear Path      "); // Extra spaces to clear text
    }

    delay(500); // Stability delay
}