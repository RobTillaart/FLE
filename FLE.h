#pragma once
//
//    FILE: FLE.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-21
// VERSION: 0.1.2
// PURPOSE: Arduino library for float with error datatype
//     URL: https://github.com/RobTillaart/FLE
//
// HISTORY:
// see FLE.cpp file


#include "Arduino.h"
#include "math.h"

#define FLE_LIB_VERSION      (F("0.1.2"))


class FLE: public Printable
{
  public:
  // CONSTRUCTOR
  FLE(float val = 0, float error = 0);

  // PRINTABLE
  size_t printTo(Print& p) const;
  FLE    setDecimals(uint8_t n) { _decimals = n;  return *this; };
  FLE    setSeparator(char c)   { _sep = c; return *this; };

  // BASE FUNCTIONS
  float value()    const{ return _v; };
  float error()    const{ return _e; };
  float relError() const{ return (_v == 0 ? 0 : abs(_e / _v)); };
  float high()     const{ return _v + _e; };
  float low()      const{ return _v - _e; };

  // MATH OPERATORS
  FLE operator -  ();  // negation  c = -a;

  FLE operator +  (const FLE&);
  FLE operator -  (const FLE&);  // minus  c = a - b;
  FLE operator *  (const FLE&);
  FLE operator /  (const FLE&);
  FLE operator += (const FLE&);
  FLE operator -= (const FLE&);
  FLE operator *= (const FLE&);
  FLE operator /= (const FLE&);


  // BOOL OPERATORS
  bool operator == (const FLE&);
  bool operator != (const FLE&);
  // FLE operator >= (const FLE&);
  // FLE operator >  (const FLE&);
  // FLE operator <= (const FLE&);
  // FLE operator < (const FLE&);


  // BOOL OPERATIONS fuzzy ones.
  // FLE operator ~= (const FLE&);  // possible equal 

  // FLE operator ~< (const FLE&);  // possible smaller
  // there are possible values of a smaller than b

  // FLE operator ~> (const FLE&);  // possible larger
  // there are possible values of a larger than b

  // investigate set like math.
  FLE both(FLE a, FLE b);    // overlap.
  // FLE sub(FLE a, FLE b);     // part of a lower than b;
  // FLE sup(FLE a, FLE b);     // part of a higher than b;
  //
  // infinite
  // NAN


  private:
  float   _v;
  float   _e;
  uint8_t _decimals = 2;
  char    _sep = '~';   //  _sep = '±';  // gives warning.
};


// -- END OF FILE --
