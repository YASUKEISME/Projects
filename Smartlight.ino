#include <Bounce2.h>

Bounce debouncer1 = Bounce(); // Create a Bounce object for IR1
Bounce debouncer2 = Bounce(); // Create a Bounce object for IR2
Bounce debouncer3 = Bounce(); // Create a Bounce object for IR3

const long interval = 2000; // 2-second interval

int ir1Pin = 8; // Pin for IR sensor 1
int ir2Pin = 12; // Pin for IR sensor 2
int ir3Pin = 13; // Pin for IR sensor 3
int ldrPin = 7; // Pin for LDR sensor
int led1Pin = 6; // Pin for LED1
int led2Pin = 5; // Pin for LED2
int led3Pin = 3; // Pin for LED3

int ir1State; // Variable to store the state of IR sensor 1
int ir2State; // Variable to store the state of IR sensor 2
int ir3State; // Variable to store the state of IR sensor 3
int lightState; // Variable to store the state of the LDR sensor

bool led1State = false; // State of LED1
bool led2State = false; // State of LED2
bool led3State = false; // State of LED3

unsigned long previousMillis1 = 0; // Previous time for LED1
unsigned long previousMillis2 = 0; // Previous time for LED2
unsigned long previousMillis3 = 0; // Previous time for LED3

void setup() {
  pinMode(ir1Pin, INPUT); // Configure IR1 as input
  pinMode(ir2Pin, INPUT); // Configure IR2 as input
  pinMode(ir3Pin, INPUT); // Configure IR3 as input
  pinMode(ldrPin, INPUT); // Configure LDR as input
  pinMode(led1Pin, OUTPUT); // Configure LED1 as output
  pinMode(led2Pin, OUTPUT); // Configure LED2 as output
  pinMode(led3Pin, OUTPUT); // Configure LED3 as output

  debouncer1.attach(ir1Pin); // Attach the debouncer to IR1
  debouncer1.interval(5); // Set debounce interval to 5 milliseconds

  debouncer2.attach(ir2Pin); // Attach the debouncer to IR2
  debouncer2.interval(5); // Set debounce interval to 5 milliseconds

  debouncer3.attach(ir3Pin); // Attach the debouncer to IR3
  debouncer3.interval(5); // Set debounce interval to 5 milliseconds

  analogWrite(led1Pin, 51); // Set initial brightness to 20% (51 out of 255)
  analogWrite(led2Pin, 51); // Set initial brightness to 20% (51 out of 255)
  analogWrite(led3Pin, 51); // Set initial brightness to 20% (51 out of 255)
}

void loop() {
  handleIRMotion(); // Handle motion detected by IR sensors
  delay(10); // Small delay for stability
}

void handleIRMotion() {
  debouncer1.update(); // Update debouncer 1
  debouncer2.update(); // Update debouncer 2
  debouncer3.update(); // Update debouncer 3

  lightState = digitalRead(ldrPin); // Read the state of the LDR sensor

  if (lightState == HIGH) { // Night (dark)
    if (debouncer1.read() == LOW) { // Motion detected by IR1
      analogWrite(led1Pin, 255); // Set brightness to 100% (255 out of 255)
      led1State = true; // Set the state of LED1 to on
      previousMillis1 = millis(); // Record the detection time
      delay(100); // Delay to avoid false triggers
    } else if (led1State && (millis() - previousMillis1 >= interval)) {
      // 2 seconds elapsed and LED1 is on
      analogWrite(led1Pin, 51); // Set brightness to 20% (51 out of 255)
      led1State = false; // Set the state of LED1 to off
    }

    if (debouncer2.read() == LOW) { // Motion detected by IR2
      analogWrite(led2Pin, 255); // Set brightness to 100% (255 out of 255)
      led2State = true; // Set the state of LED2 to on
      previousMillis2 = millis(); // Record the detection time
      delay(100); // Delay to avoid false triggers
    } else if (led2State && (millis() - previousMillis2 >= interval)) {
      // 2 seconds elapsed and LED2 is on
      analogWrite(led2Pin, 51); // Set brightness to 20% (51 out of 255)
      led2State = false; // Set the state of LED2 to off
    }

    if (debouncer3.read() == LOW) { // Motion detected by IR3
      analogWrite(led3Pin, 255); // Set brightness to 100% (255 out of 255)
      led3State = true; // Set the state of LED3 to on
      previousMillis3 = millis(); // Record the detection time
      delay(100); // Delay to avoid false triggers
    } else if (led3State && (millis() - previousMillis3 >= interval)) {
      // 2 seconds elapsed and LED3 is on
      analogWrite(led3Pin, 51); // Set brightness to 20% (51 out of 255)
      led3State = false; // Set the state of LED3 to off
    }
  } else { // Day (bright)
    analogWrite(led1Pin, 0); // Turn off LED1
    analogWrite(led2Pin, 0); // Turn off LED2
    analogWrite(led3Pin, 0); // Turn off LED3
  }
}
