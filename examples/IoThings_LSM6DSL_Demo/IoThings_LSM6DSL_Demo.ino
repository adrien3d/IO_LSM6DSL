/***************************************************************************
  This is a library for the LSM6DSL humidity, temperature & pressure sensor

  Designed to work with all kinds of LSM6DSL Breakout

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Written by Adrien Chapelet for IoThings
 ***************************************************************************/
 
#include <Wire.h>
#include <SPI.h>
#include <IO_LSM6DSL.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10


IO_LSM6DSL bme; // I2C
//IO_LSM6DSL bme(BME_CS); // hardware SPI
//IO_LSM6DSL bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

void setup() {
  Serial.begin(9600);
  Serial.println(F("LSM6DSL test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid LSM6DSL sensor, check wiring!");
    while (1);
  }
}

void loop() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.print("Pres at sea level = ");
    Serial.print(bme.seaLevelForAltitude(110.6, 1023.4));
    Serial.println(" hPa");

    Serial.println();
    delay(500);
}
