/****************************************************************
Jorrel Rajan
some code that reads acceleration data: prints (X, Y, Z)
uses that prototype computer shit (SDA 26 SCL 27)
****************************************************************/

// Include the KXTJ3-1057 library (includes Wire.h)
#include "kxtj3-1057.h"
#include <Wire.h>

float sampleRate =
    6.25; // HZ - Samples per second - 0.781, 1.563, 3.125, 6.25,
          // 12.5, 25, 50, 100, 200, 400, 800, 1600Hz
          // Sample rates ≥ 400Hz force High Resolution mode on
uint8_t accelRange = 2; // Accelerometer range = 2, 4, 8, 16g
bool highRes = false; // High Resolution mode on/off

KXTJ3 myIMU(0x0F); // Address can be 0x0E or 0x0F

void setup()
{

  Wire.setPins(26, 27);
  Wire.begin();

  Serial.begin(115200);
  delay(5000); // wait until serial is open...
  
  if (myIMU.begin(sampleRate, accelRange, highRes) ==
  IMU_SUCCESS) {
    Serial.println("IMU initialized.");
  } else {
    Serial.println("Failed to initialize IMU.");
    while(true); // stop running sketch if failed
  }

  uint8_t readData = 0;

  // Get the ID:
  if (myIMU.readRegister(&readData, KXTJ3_WHO_AM_I) ==
  IMU_SUCCESS) {
  Serial.print("Who am I? 0x");
  Serial.println(readData, HEX);
  } else {
    Serial.println("Communication error, stopping.");
	while(true); // stop running sketch if failed
  }

  Serial.println();

}

void loop()
{

  myIMU.standby(false);

  uint8_t dataLowRes = 0;

  if (myIMU.readRegister(&dataLowRes, KXTJ3_XOUT_H) ==
  IMU_SUCCESS) {
    // Read accelerometer data in mg as Float
    Serial.print(myIMU.axisAccel(X), 4);
    Serial.print(",");
  }


  if (myIMU.readRegister(&dataLowRes, KXTJ3_YOUT_H) ==
  IMU_SUCCESS) {
    // Read accelerometer data in mg as Float
    Serial.print(myIMU.axisAccel(Y), 4);
    Serial.print(",");
  }

  if (myIMU.readRegister(&dataLowRes, KXTJ3_ZOUT_H) ==
  IMU_SUCCESS) {
    // Read accelerometer data in mg as Float
    Serial.println(myIMU.axisAccel(Z), 4);
  }
  
}