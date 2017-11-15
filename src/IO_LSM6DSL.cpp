/***************************************************************************
  This is a library for the LSM6DSL humidity, temperature & pressure sensor

  Designed to work with all kinds of LSM6DSL Breakout

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Written by Adrien Chapelet for IoThings
 ***************************************************************************/

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>

#include "IO_LSM6DSL.h"

/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/


IO_LSM6DSL::IO_LSM6DSL()
  : _cs(-1), _mosi(-1), _miso(-1), _sck(-1)
{ }

IO_LSM6DSL::IO_LSM6DSL(int8_t cspin)
  : _cs(cspin), _mosi(-1), _miso(-1), _sck(-1)
{ }

IO_LSM6DSL::IO_LSM6DSL(int8_t cspin, int8_t mosipin, int8_t misopin, int8_t sckpin)
  : _cs(cspin), _mosi(mosipin), _miso(misopin), _sck(sckpin)
{ }


bool IO_LSM6DSL::begin(uint8_t a) {
  _i2caddr = a;

  if (_cs == -1) {
    // i2c
    Wire.begin();
  } else {
    digitalWrite(_cs, HIGH);
    pinMode(_cs, OUTPUT);

    if (_sck == -1) {
      // hardware SPI
      SPI.begin();
    } else {
      // software SPI
      pinMode(_sck, OUTPUT);
      pinMode(_mosi, OUTPUT);
      pinMode(_miso, INPUT);
    }
  }

  if (read8(LSM6DSL_REGISTER_CHIPID) != 0x60)
    return false;

  readCoefficients();

  //Set before CONTROL_meas (DS 5.4.3)
  write8(LSM6DSL_REGISTER_CONTROLHUMID, 0x05); //16x oversampling 

  write8(LSM6DSL_REGISTER_CONTROL, 0xB7); // 16x ovesampling, normal mode
  return true;
}

uint8_t IO_LSM6DSL::spixfer(uint8_t x) {
  if (_sck == -1)
    return SPI.transfer(x);

  // software spi
  //Serial.println("Software SPI");
  uint8_t reply = 0;
  for (int i=7; i>=0; i--) {
    reply <<= 1;
    digitalWrite(_sck, LOW);
    digitalWrite(_mosi, x & (1<<i));
    digitalWrite(_sck, HIGH);
    if (digitalRead(_miso))
      reply |= 1;
  }
  return reply;
}

/**************************************************************************/
/*!
    @brief  Writes an 8 bit value over I2C/SPI
*/
/**************************************************************************/
void IO_LSM6DSL::write8(byte reg, byte value)
{
  if (_cs == -1) {
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.write((uint8_t)value);
    Wire.endTransmission();
  } else {
    if (_sck == -1)
      SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs, LOW);
    spixfer(reg & ~0x80); // write, bit 7 low
    spixfer(value);
    digitalWrite(_cs, HIGH);
    if (_sck == -1)
      SPI.endTransaction();              // release the SPI bus
  }
}

/**************************************************************************/
/*!
    @brief  Reads an 8 bit value over I2C
*/
/**************************************************************************/
uint8_t IO_LSM6DSL::read8(byte reg)
{
  uint8_t value;

  if (_cs == -1) {
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)_i2caddr, (byte)1);
    value = Wire.read();

  } else {
    if (_sck == -1)
      SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs, LOW);
    spixfer(reg | 0x80); // read, bit 7 high
    value = spixfer(0);
    digitalWrite(_cs, HIGH);
    if (_sck == -1)
      SPI.endTransaction();              // release the SPI bus
  }
  return value;
}

/**************************************************************************/
/*!
    @brief  Reads a 16 bit value over I2C
*/
/**************************************************************************/
uint16_t IO_LSM6DSL::read16(byte reg)
{
  uint16_t value;

  if (_cs == -1) {
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)_i2caddr, (byte)2);
    value = (Wire.read() << 8) | Wire.read();

  } else {
    if (_sck == -1)
      SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs, LOW);
    spixfer(reg | 0x80); // read, bit 7 high
    value = (spixfer(0) << 8) | spixfer(0);
    digitalWrite(_cs, HIGH);
    if (_sck == -1)
      SPI.endTransaction();              // release the SPI bus
  }

  return value;
}

uint16_t IO_LSM6DSL::read16_LE(byte reg) {
  uint16_t temp = read16(reg);
  return (temp >> 8) | (temp << 8);

}

/**************************************************************************/
/*!
    @brief  Reads a signed 16 bit value over I2C
*/
/**************************************************************************/
int16_t IO_LSM6DSL::readS16(byte reg)
{
  return (int16_t)read16(reg);

}

int16_t IO_LSM6DSL::readS16_LE(byte reg)
{
  return (int16_t)read16_LE(reg);

}


/**************************************************************************/
/*!
    @brief  Reads a 24 bit value over I2C
*/
/**************************************************************************/

uint32_t IO_LSM6DSL::read24(byte reg)
{
  uint32_t value;

  if (_cs == -1) {
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)_i2caddr, (byte)3);
    
    value = Wire.read();
    value <<= 8;
    value |= Wire.read();
    value <<= 8;
    value |= Wire.read();

  } else {
    if (_sck == -1)
      SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs, LOW);
    spixfer(reg | 0x80); // read, bit 7 high
    
    value = spixfer(0);
    value <<= 8;
    value |= spixfer(0);
    value <<= 8;
    value |= spixfer(0);

    digitalWrite(_cs, HIGH);
    if (_sck == -1)
      SPI.endTransaction();              // release the SPI bus
  }

  return value;
}


/**************************************************************************/
/*!
    @brief  Reads the factory-set coefficients
*/
/**************************************************************************/
void IO_LSM6DSL::readCoefficients(void)
{
    _LSM6DSL_calib.dig_T1 = read16_LE(LSM6DSL_REGISTER_DIG_T1);
    _LSM6DSL_calib.dig_T2 = readS16_LE(LSM6DSL_REGISTER_DIG_T2);
    _LSM6DSL_calib.dig_T3 = readS16_LE(LSM6DSL_REGISTER_DIG_T3);

    _LSM6DSL_calib.dig_P1 = read16_LE(LSM6DSL_REGISTER_DIG_P1);
    _LSM6DSL_calib.dig_P2 = readS16_LE(LSM6DSL_REGISTER_DIG_P2);
    _LSM6DSL_calib.dig_P3 = readS16_LE(LSM6DSL_REGISTER_DIG_P3);
    _LSM6DSL_calib.dig_P4 = readS16_LE(LSM6DSL_REGISTER_DIG_P4);
    _LSM6DSL_calib.dig_P5 = readS16_LE(LSM6DSL_REGISTER_DIG_P5);
    _LSM6DSL_calib.dig_P6 = readS16_LE(LSM6DSL_REGISTER_DIG_P6);
    _LSM6DSL_calib.dig_P7 = readS16_LE(LSM6DSL_REGISTER_DIG_P7);
    _LSM6DSL_calib.dig_P8 = readS16_LE(LSM6DSL_REGISTER_DIG_P8);
    _LSM6DSL_calib.dig_P9 = readS16_LE(LSM6DSL_REGISTER_DIG_P9);

    _LSM6DSL_calib.dig_H1 = read8(LSM6DSL_REGISTER_DIG_H1);
    _LSM6DSL_calib.dig_H2 = readS16_LE(LSM6DSL_REGISTER_DIG_H2);
    _LSM6DSL_calib.dig_H3 = read8(LSM6DSL_REGISTER_DIG_H3);
    _LSM6DSL_calib.dig_H4 = (read8(LSM6DSL_REGISTER_DIG_H4) << 4) | (read8(LSM6DSL_REGISTER_DIG_H4+1) & 0xF);
    _LSM6DSL_calib.dig_H5 = (read8(LSM6DSL_REGISTER_DIG_H5+1) << 4) | (read8(LSM6DSL_REGISTER_DIG_H5) >> 4);
    _LSM6DSL_calib.dig_H6 = (int8_t)read8(LSM6DSL_REGISTER_DIG_H6);
}

/**************************************************************************/
/*!

*/
/**************************************************************************/
float IO_LSM6DSL::readTemperature(void)
{
  int32_t var1, var2;

  int32_t adc_T = read24(LSM6DSL_REGISTER_TEMPDATA);
  adc_T >>= 4;

  var1  = ((((adc_T>>3) - ((int32_t)_LSM6DSL_calib.dig_T1 <<1))) *
	   ((int32_t)_LSM6DSL_calib.dig_T2)) >> 11;

  var2  = (((((adc_T>>4) - ((int32_t)_LSM6DSL_calib.dig_T1)) *
	     ((adc_T>>4) - ((int32_t)_LSM6DSL_calib.dig_T1))) >> 12) *
	   ((int32_t)_LSM6DSL_calib.dig_T3)) >> 14;

  t_fine = var1 + var2;

  float T  = (t_fine * 5 + 128) >> 8;
  return T/100;
}
