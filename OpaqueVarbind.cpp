

#ifndef __OPAQUEVARBIND_H__
#include "OpaqueVarbind.h"
#endif

#ifndef _WIN32
#  include <ctype.h>
#endif

#ifndef __COMPAT_H__
#include "compat.h"
#endif

#include <memory.h>
#include <ctype.h>

OpaqueVarbind::OpaqueVarbind()
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{

}

OpaqueVarbind::OpaqueVarbind(unsigned char* value, unsigned int length)
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{
  mData = new unsigned char [length];
  Value(value, length);
}

OpaqueVarbind::OpaqueVarbind(char* value, unsigned int length)
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{
  mData = new unsigned char [length];
  Value(value, length);
}

OpaqueVarbind::OpaqueVarbind(char value)
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{
  mData = new unsigned char[1];
  Value(value);
}

OpaqueVarbind::OpaqueVarbind(unsigned long value)
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{
  DataLength((unsigned short)((value / 255) + 1));
  mData = new unsigned char [sizeof(unsigned long)];
  memcpy(mData, &value, sizeof(unsigned long));
}

OpaqueVarbind::OpaqueVarbind(long value)  
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{
  DataLength((unsigned short)((value / 255) + 1));
  mData = new unsigned char [sizeof(long)];
  memcpy(mData, &value, sizeof(long));
}

OpaqueVarbind::OpaqueVarbind(unsigned char value)
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{

}

OpaqueVarbind::OpaqueVarbind(unsigned int value)
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{
  DataLength((unsigned short)((value / 255) + 1));
  mData = new unsigned char [sizeof(unsigned int)];
  *mData = value;
}

OpaqueVarbind::OpaqueVarbind(int value)
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{
  DataLength((unsigned short)((value / 255) + 1));
  mData = new unsigned char [sizeof(int)];
  *mData = value;
}

OpaqueVarbind::OpaqueVarbind(unsigned short value)
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{
  DataLength((unsigned short)((value / 255) + 1));
  mData = new unsigned char [sizeof(unsigned short)];
  memcpy(mData, &value, sizeof(unsigned short));
}

OpaqueVarbind::OpaqueVarbind(short value)
              :Varbind(SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{
  DataLength((unsigned short)((value / 255) + 1));
  mData = new unsigned char [sizeof(int)];
  memcpy(mData, &value, sizeof(short));
}

OpaqueVarbind::OpaqueVarbind(unsigned char* &pduPart)
              :Varbind(pduPart, SNMPOPAQUE, "Opaque"),
	       mData(NULL)
{
  mData = new unsigned char [DataLength()];
  memcpy(mData, pduPart, DataLength());
  pduPart += DataLength();
}

OpaqueVarbind::~OpaqueVarbind()
{
  if (mData != NULL)
    delete [] mData;
}

const char*
OpaqueVarbind::Printable()
{
  if (mPrintable == NULL)
  {
    unsigned short len = DataLength();
    mPrintable = new char [len + 1];
    for (unsigned short i = 0; i < len; i++)
    {
      if (isprint(mData[i]))
	mPrintable[i] = mData[i];
      else
	mPrintable[i] = ' ';
    }
    mPrintable[len] = '\0';
  }
  return mPrintable;
}

void
OpaqueVarbind::Value(unsigned char* value, unsigned int length)
{
  DataLength(length);
  memcpy(mData, value, length);
}

void                   
OpaqueVarbind::Value(char* value, unsigned int length)
{
  DataLength(length);
  memcpy(mData, value, length);
}

void                   
OpaqueVarbind::Value(char value)
{
  DataLength(1);
  *mData = value;
}

void                   
OpaqueVarbind::Value(unsigned long value)
{
  DataLength((unsigned short)(value / 255) + 1);
}

void                   
OpaqueVarbind::Value(long value)  
{
  DataLength((unsigned short)(value / 255) + 1);
}

void                   
OpaqueVarbind::Value(unsigned char value)
{
  DataLength((unsigned short)((value / 255) + 1));
}

void                   
OpaqueVarbind::Value(unsigned int value)
{
  DataLength((unsigned short)((value / 255) + 1));
}

void                   
OpaqueVarbind::Value(int value)
{
  DataLength((unsigned short)((value / 255) + 1));
}

void                   
OpaqueVarbind::Value(unsigned short value)
{
  DataLength((unsigned short)((value / 255) + 1));
}

void                   
OpaqueVarbind::Value(short value)
{
  DataLength((unsigned short)((value / 255) + 1));
}

const char*
OpaqueVarbind::Value()
{
  return (const char*)mData;
}

void
OpaqueVarbind::Build(unsigned char*& pdu)
{
  unsigned int len = DataLength();
  unsigned int lenLen = (len / 129) + 1;
  pdu[0] = SNMPOPAQUE;
  unsigned char* lPdu = pdu;
  lPdu++;
  encodeLength(lPdu, (long)len);
  memcpy(&pdu[lenLen + 1], mData, len); // the tag too  
}

unsigned char* 
OpaqueVarbind::Data()
{
  unsigned int len = DataLength();
  unsigned int lenLen = (len / 129) + 1;
  unsigned char* data = new unsigned char [len + lenLen + 1];
  unsigned char* retVal = data;
  Build(data);
  return retVal;
}
