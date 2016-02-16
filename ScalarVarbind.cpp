#ifndef __SCALARVARBIND_H__
#  include "ScalarVarbind.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef __COMPAT_H__
#include "compat.h"
#endif

ScalarVarbind::ScalarVarbind(unsigned short type, const char* typeString)
              :Varbind(type, typeString),
	       mValue(0)

{

}

ScalarVarbind::ScalarVarbind(unsigned char* &pduPart, 
			     unsigned short type, 
			     const char* typeString)
              :Varbind(pduPart, type, typeString),
	       mValue(0)

{

}

ScalarVarbind::ScalarVarbind()
{

}

unsigned char*   
ScalarVarbind::Data()
{
  unsigned char* data = new unsigned char [DataLength() + 2];
  unsigned char* retVal = data;
  Build(data);
  return retVal;
}

const char*      
ScalarVarbind::Printable()
{
  if (mPrintable == NULL)
  {
    int size = DataLength() * 10 + 10;
    mPrintable = new char[size];
    memset(mPrintable, 0, size);    
#ifdef _WIN32
    sprintf_s(mPrintable, size, "%ld", mValue);
#else
    sprintf(mPrintable, "%ld", mValue);
#endif
  }
  return mPrintable;
}

//#include <iostream.h>
void             
ScalarVarbind::Build(unsigned char*& pdu)
{
  //  cout << "length = " << DataLength() << endl;
  //  unsigned char* origPdu = pdu;

  encodeLength(pdu, DataLength());
  int shiftsize = 8 * (DataLength() - 1);
  for (unsigned int i = 0; i < DataLength(); i++, shiftsize -= 8)
  {
    *pdu++ = (unsigned char)((mValue >> shiftsize) & 0x000000ff);
  }
  //  printf("data in pdu: %02x %02x, %02x %02x\r\n", origPdu[0], origPdu[1], origPdu[2], origPdu[3]);
}

void 
ScalarVarbind::Value(unsigned long value)
{
  
  if (value == 0)
  {
    mValue = value;
    DataLength(1);
  }
  else
  {
    int intsize = sizeof(unsigned long);
    int loopCount = 0;
    
    unsigned long mask = 0xff800000;// >> ((8 * (sizeof(unsigned int) - 1)) - 1);
    unsigned long valueIn = value;
    while((((valueIn & mask) == 0) || ((valueIn & mask) == mask))
	  && intsize > 1)
    {
      intsize--;
      loopCount++;
      valueIn <<= 8;
    }
    //    for (int x = 0; x < loopCount; x++)
    //      value >>= 8;
    mValue = value;
    DataLength(intsize);
  }
}



