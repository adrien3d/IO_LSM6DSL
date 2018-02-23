/***************************************************************************
  This is a library for the LSM6DSL accelerometer & gyroscope sensor

  Designed to work with all kinds of LSM6DSL Breakout

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Written by Adrien Chapelet for IoThings
 ***************************************************************************/
 
#include <Wire.h>
#include <SPI.h>
#include <IO_LSM6DSL.h>

#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11
#define LSM_CS 10


IO_LSM6DSL lsm; // I2C
//IO_LSM6DSL lsm(LSM_CS); // hardware SPI
//IO_LSM6DSL lsm(LSM_CS, LSM_MOSI, LSM_MISO, LSM_SCK);

void setup() {
  Serial.begin(9600);
  Serial.println(F("LSM6DSL test"));

  if (!lsm.begin(1)) {
    Serial.println("Could not find a valid LSM6DSL sensor, check wiring!");
    while (1);
  }
}

void loop() {
  //Get all parameters
  Serial.print("\nAccelerometer:\n");
  Serial.print(" X = ");
  Serial.println(lsm.readFloatAccelX(), 4);
  Serial.print(" Y = ");
  Serial.println(lsm.readFloatAccelY(), 4);
  Serial.print(" Z = ");
  Serial.println(lsm.readFloatAccelZ(), 4);

  Serial.print("\nGyroscope:\n");
  Serial.print(" X = ");
  Serial.println(lsm.readFloatGyroX(), 4);
  Serial.print(" Y = ");
  Serial.println(lsm.readFloatGyroY(), 4);
  Serial.print(" Z = ");
  Serial.println(lsm.readFloatGyroZ(), 4);

  Serial.print("Temperature = ");
  Serial.print(lsm.readTemperature());
  Serial.println(" °C");

  Serial.println();
  delay(500);
}
