#include <Servo.h>

Servo horizontal; 
Servo vertical;

int servoH = 180; // Initial position of the horizontal servo
int servoHLimitHigh = 175; // Upper limit of the horizontal servo
int servoHLimitLow = 5; // Lower limit of the horizontal servo
// 65 degrees max

int servoV = 180; // Initial position of the vertical servo
int servoVLimitHigh = 180; // Upper limit of the vertical servo
int servoVLimitLow = 1; // Lower limit of the vertical servo

int ldrLT = A0; // LDR top left
int ldrRT = A1; // LDR top right
int ldrLD = A3; // LDR bottom left
int ldrRD = A2; // LDR bottom right

void setup() {
  horizontal.attach(9); // Attach horizontal servo to pin 9
  vertical.attach(10); // Attach vertical servo to pin 10
}

void loop() {
  handleLightDirection();
}

void handleLightDirection() {
  int lt = analogRead(ldrLT); // Read top left LDR
  int rt = analogRead(ldrRT); // Read top right LDR
  int ld = analogRead(ldrLD); // Read bottom left LDR
  int rd = analogRead(ldrRD); // Read bottom right LDR
  int dTime = 10; // Delay time
  int tol = 90; // Tolerance
  int avt = (lt + rt) / 2; // Average value top
  int avd = (ld + rd) / 2; // Average value bottom
  int avl = (lt + ld) / 2; // Average value left
  int avr = (rt + rd) / 2; // Average value right
  int dVert = avt - avd; // Difference between top and bottom
  int dHoriz = avl - avr; // Difference between left and right

  // Check if light intensity is stable
  if (dVert >= -tol && dVert <= tol && dHoriz >= -tol && dHoriz <= tol) {
    // Stay inactive until a notable change occurs
    delay(2000); // Reduced delay to 2 seconds for quicker response
  } else {
    // Move the servos towards the direction of the light
    moveServos(dVert, dHoriz, tol, avt, avd, avl, avr);
  }
  delay(dTime);
}

void moveServos(int dVert, int dHoriz, int tol, int avt, int avd, int avl, int avr) {
  if (-tol > dVert || dVert > tol) {
    if (avt > avd) {
      servoV++;
      if (servoV > servoVLimitHigh) {
        servoV = servoVLimitHigh;
      }
    } else if (avt < avd) {
      servoV--;
      if (servoV < servoVLimitLow) {
        servoV = servoVLimitLow;
      }
    }
    vertical.write(servoV); // Write position to the vertical servo
  }

  if (-tol > dHoriz || dHoriz > tol) {
    if (avl > avr) {
      servoH--;
      if (servoH < servoHLimitLow) {
        servoH = servoHLimitLow;
      }
    } else if (avl < avr) {
      servoH++;
      if (servoH > servoHLimitHigh) {
        servoH = servoHLimitHigh;
      }
    }
    horizontal.write(servoH); // Write position to the horizontal servo
  }
}
