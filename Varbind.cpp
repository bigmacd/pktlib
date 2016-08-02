

#ifndef __VARBIND_H__
#include "Varbind.h"
#endif

//#include <iostream.h>

Varbind::Varbind()
{}

Varbind::Varbind(unsigned short type, const char* typeString)
        :Next(0L),
	 mType(type),
	 mTypeString(typeString),
	 mLength(0),
	 mPrintable(0L)
{

}

Varbind::Varbind(unsigned char* &pduPart,
		 unsigned short type, 
		 const char* typeString)
        :Next(0L),
	 mType(type),
	 mTypeString(typeString),
	 mLength(0),
	 mPrintable(0L)
{
  // pointing to the length field
  long value = 0;
  ::decodeLength(pduPart, &value);

  // set the length in the varbind
  DataLength((unsigned short)value);

#if 0
  // get the storage
  unsigned char* data = new unsigned char[value];

  // put the data into it
  memcpy(data, pduPart, value);

  // adjust the incoming buffer
  pduPart += value;
  
  // set the data in the varbind
  Data(data);
#endif
}

Varbind::~Varbind()
{
  if (mPrintable) { 
    delete [] mPrintable;
    mPrintable = NULL;
  }
}

unsigned int
Varbind::Length()
{
  unsigned int len = 0;
  len += DataLength();
  len++; // the tag
  len += calculateLengthLength(len);
  return len;
}

unsigned int
ComputeIntValue(unsigned char* &pduPart, unsigned int size)
{
  return (unsigned int)ComputeLongValue(pduPart, size);
}

unsigned long
ComputeLongValue(unsigned char* &pduPart, unsigned int size)
{

  unsigned long value = 0;
  unsigned int shiftsize = 8;
  unsigned int origSize = size;
  

  int negBit = 1;
  negBit = negBit << ((shiftsize * size) - 1);

  value = *pduPart++;
  for (; size > 1; size--)
  {
    value = value << shiftsize;
    value |= *pduPart++;
  }

  if (negBit & value)
  {
    unsigned long bitMask = 0xff000000;
    for (; origSize < sizeof(unsigned long); origSize++)
    {
      value |= bitMask;
      bitMask = bitMask >> shiftsize;
    }
  }


  return value;
}

__int64
Compute64Value(unsigned char* &pduPart, unsigned int size)
{

  __int64 value = 0;
  unsigned int shiftsize = 8;
  unsigned int origSize = size;
  

  // only counters are 64 bits, no negative valuies
  // int negBit = 1;
  // negBit = negBit << ((shiftsize * size) - 1);

  value = *pduPart++;
  for (; size > 1; size--)
  {
    value = value << shiftsize;
    value |= *pduPart++;
  }

  //if (negBit & value)
  //{
  //  unsigned long bitMask = 0xff000000;
  //  for (; origSize < sizeof(unsigned long); origSize++)
  //  {
  //    value |= bitMask;
  //    bitMask = bitMask >> shiftsize;
  //  }
  //}

  return value;
}

