//
//    FILE: FLE.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-21
// VERSION: 0.1.3
// PURPOSE: Arduino library for float with error datatype
//     URL: https://github.com/RobTillaart/FLE
//
//  HISTORY
//  0.0.1  2020-07-21  initial version
//  0.1.0  2020-12-23  arduino-CI + unit tests
//  0.1.1  2021-05-27  fix arduino-lint
//  0.1.2  2021-06-15  add negation + unit tests
//                     add first comparisons + some experimental
//  0.1.3  2021-06-16  add shared() 


#include "FLE.h"


FLE::FLE(float val, float err)
{
  _v = val;
  _e = abs(err);
};


// PRINTABLE
size_t FLE::printTo(Print& p) const
{
  size_t n = 0;
  n += p.print(_v, _decimals);
  n += p.print(' ');
  n += p.print(_sep);
  n += p.print(' ');
  n += p.print(_e, _decimals);
  return n;
}


/////////////////////////////////////////////////
//
// MATH OPERATORS
//


// NEGATION
FLE FLE::operator - ()
{
  return FLE(-_v, _e);
}


FLE FLE::operator + (const FLE &in)
{
  return FLE(_v + in._v, _e + in._e);
}


// SUBTRACT
FLE FLE::operator - (const FLE &in)
{
  return FLE(_v - in._v, _e + in._e);
}


FLE FLE::operator * (const FLE &in)
{
  float val = _v * in._v;
  float err = (relError() + in.relError()) * val;
  return FLE(val, err);
}


FLE FLE::operator / (const FLE &in)
{
  float val = _v / in._v;
  float err = (relError() + in.relError()) * val;
  return FLE(val, err);
}


FLE FLE::operator += (const FLE &in)
{
  _v += in._v;
  _e += in._e;
  return *this;
}


FLE FLE::operator -= (const FLE &in)
{
  _v -= in._v;
  _e += in._e;
  return *this;
}


FLE FLE::operator *= (const FLE &in)
{
  float sum = relError() + in.relError();
  _v *= in._v;
  _e =  sum * _v;
  return *this;
}


FLE FLE::operator /= (const FLE &in)
{
  float sum = relError() + in.relError();
  _v /= in._v;
  _e =  sum * _v;
  return *this;
}


/////////////////////////////////////////////////
//
// BOOL OPERATORS
//
// bool FLE::operator == (const FLE in)
//{
//  return ((_v == in._v) && (_e == in._e));
//}

bool FLE::operator == (const FLE &in)
{
  return ((_v == in._v) && (_e == in._e));
}

bool FLE::operator != (const FLE &in)
{
  return ((_v != in._v) || (_e != in._e));
}

// bool FLE::operator >= (const FLE &in)
// {
  // return ((*this == in) || (low() >= in.high()));
// }

bool FLE::operator > (const FLE &in)
{
  return low() > in.high();
}

// bool FLE::operator <= (const FLE &in)
// {
  // return ((*this == in) || (high() <= in.low()) );
// }

bool FLE::operator < (const FLE &in)
{
  return high() < in.low();
}



/////////////////////////////////////////////////
//
// MISC OPERATORS
//
bool FLE::in(FLE a)
{
  return ( a.low() <= low() && high() <= a.high());
}


FLE FLE::shared(FLE a)
{
  float v, e;
  // six possible cases.
  // case 1, 6
  if ((*this < a) || (*this > a)) return FLE(NAN, NAN);  // no overlap

  // case 3, 4
  if (a.in(*this)) return a;
  if (this->in(a)) return *this;

  // case 2
  if (low() < a.low())
  {
    v = (a.low() + high())/2;
    e = v - a.low();
  }
  // case 5
  else
  {
    v = (low() + a.high())/2;
    e = v - low();
  }
  return FLE(v, e);
}


FLE FLE::lower(FLE a)
{
  return FLE(0,0);   // TODO
}


FLE FLE::higher(FLE a)
{
  return FLE(0,0);   // TODO 
}


/////////////////////////////////////////////////
//
// WEAK PROPOSITIONS
//
// possible equal 
bool FLE::peq(const FLE &in)
{
  if (in.low() <= low() && in.high() >= low() ) return true;
  if (low() <= in.low() && high() >= in.low() ) return true;
  return false;
}

// possible not equal
bool FLE::pne(const FLE &in)
{
  return !(*this == in);
}

// possible less than
bool FLE::plt(const FLE &in)
{
  return true;  // TODO
}

// possible less equal
bool FLE::ple(const FLE &in)
{
  return true;  // TODO
}

// possible greater than
bool FLE::pgt(const FLE &in)
{
  return true;  // TODO
}

// possible greater equal
bool FLE::pge(const FLE &in)
{
  return true;  // TODO
}



// -- END OF FILE --
