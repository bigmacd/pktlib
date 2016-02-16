#ifndef __SCALAR64VARBIND_H__
#  include "Scalar64Varbind.h"
#endif

#if _WIN32
#  include <windows.h>
#else
#  include <stdlib.h>
#  include <string.h>
#  include <stdio.h>
#endif

Scalar64Varbind::Scalar64Varbind(unsigned short type, const char* typeString)
                :Varbind(type, typeString),
		 mValue(0)

{

}

Scalar64Varbind::Scalar64Varbind(unsigned char* &pduPart, 
				 unsigned short type, 
				 const char* typeString)
                :Varbind(pduPart, type, typeString),
		 mValue(0)

{

}

Scalar64Varbind::Scalar64Varbind()
{

}

unsigned char*   
Scalar64Varbind::Data()
{
  unsigned char* data = new unsigned char [DataLength() + 2];
  unsigned char* retVal = data;
  Build(data);
  return retVal;
}

const char*      
Scalar64Varbind::Printable()
{
  if (mPrintable == NULL)
  {
    int size = DataLength() * 10 + 10;
    mPrintable = new char[size];
    memset(mPrintable, 0, size);    
#ifdef _WIN32
    sprintf_s(mPrintable, size, "%I64lu", mValue);
#else
    sprintf(mPrintable, "%I64lu", mValue);
#endif
  }
  return mPrintable;
}
 
void             
Scalar64Varbind::Build(unsigned char*& pdu)
{
  encodeLength(pdu, DataLength());
  int shiftsize = 8 * (DataLength() - 1);
  for (unsigned int i = 0; i < DataLength(); i++, shiftsize -= 8)
  {
     *pdu++ = (unsigned char)((mValue >> shiftsize) & 0x00000000000000ff);
  }
}

void 
Scalar64Varbind::Value(__int64 value)
{
  mValue = value;
  if (value == 0)
    DataLength(1);
  else
  {

    int intsize = sizeof(__int64);
    //#if !defined(_LINUX) || !defined(_SOLARIS)
    //#ifndef _SOLARIS
    //    __int64 mask = 0xff80000000000000;// >> ((8 * (sizeof(unsigned int) - 1)) - 1);
    //#else
    __int64 mask = 0xff800000;
    mask <<= 16;
    //#endif
    __int64 valueIn = value;
    while((((valueIn & mask) == 0) || ((valueIn & mask) == mask))
	  && intsize > 1)
    {
      intsize--;
      valueIn <<= 8;
    }
    //    for (int x = 0; x < loopCount; x++)
    //      value >>= 8;

    mValue = value;
    DataLength(intsize);

  }
}

