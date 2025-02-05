#pragma once
//
//    FILE: AD7367.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2025-01-10
// PURPOSE: Arduino library for the AD7367, 2 channel simultaneous sampling 14 bit ADC.
//          Also AD7366 == 12 bits.
//     URL: https://github.com/RobTillaart/AD7367


#include "Arduino.h"

#define AD7367_LIB_VERSION        (F("0.1.1"))


class AD7367
{
public:
  //  CONSTRUCTOR
  //  pins to set.
  AD7367(uint8_t select, uint8_t clock, uint8_t convert, uint8_t busy, uint8_t data0, uint8_t data1);

  void     begin();
  uint8_t  getType();  //  returns 66 or 67
  int      getBits();  //  returns 12 or 14

  //  READ
  //  note the ADDR line below determines which pair is read (a1, b1) or (a2, b2)
  int      read();  //  reads ADC-A and ADC-B into an internal buffer.

  //  READ ASYNCHRONOUS
  void     triggerConversion();
  bool     conversionBusy();
  bool     conversionReady();
  int      readAsync();
  //  GET VALUES FROM ADC's
  int      getLastADCA();  //  returns last read value from ADC-A
  int      getLastADCB();  //  returns last read value from ADC-B

  //  FASTREAD
  //  read and return 2 measurements by reference. (arrays)
  //  a == ADC-A,  b == ADC-B
  int      fastRead(int &a, int &b);


  //  ADDR
  //  one could hard connect the ADDR pin,
  //  so these functions are not needed
  //  pin is set default LOW
  void     ADDRpin(uint8_t pin);
  //  LOW = (Va1, Vb1) or HIGH = (Va2, Vb2)
  inline void ADDRwrite(uint8_t mode) { digitalWrite(_addr, mode); };


  //  REFSEL
  //  one could hard connect the REFSEL pin,
  //  so these functions are not needed
  //  pin is set default HIGH = internal.
  void     REFSELpin(uint8_t pin);
  //  LOW = external voltage or LOW = internal 2.5 Volt. 
  inline void REFSELwrite(uint8_t mode) { digitalWrite(_refsel, mode); };

  //  OBSOLETE
  int    getValue(uint8_t channel); // 0 = ADC-A,  1 = ADC-B


protected:
  uint8_t  _type;
  uint8_t  _bits;
  uint8_t  _select;
  uint8_t  _clock;
  uint8_t  _convert;
  uint8_t  _busy;
  uint8_t  _data0;
  uint8_t  _data1;
  int16_t  _value[2] = {0, 0};

  uint8_t  _addr   = 255;
  uint8_t  _refsel = 255;
};



/////////////////////////////////////////////////////////////////////////////
//
//  DERIVED CLASS AD7366
//
class AD7366 : public AD7367
{
public:
  AD7366(uint8_t select, uint8_t clock, uint8_t convert, uint8_t busy, uint8_t data0, uint8_t data1);
};


//  -- END OF FILE --

