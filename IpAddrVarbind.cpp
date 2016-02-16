

#ifndef __IPADDRVARBIND_H__
#include "IpAddrVarbind.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

IpAddrVarbind::IpAddrVarbind()
              :Varbind(IPADDRESS, "IpAddress"),
	       mData(NULL)
{
}

IpAddrVarbind::IpAddrVarbind(unsigned char* &pduPart)
              :Varbind(pduPart, IPADDRESS, "IpAddress"),
	       mData(NULL)
{
  mData = new unsigned char [DataLength()];
  memcpy(mData, pduPart, DataLength());
  pduPart += DataLength();
}

IpAddrVarbind::IpAddrVarbind(char* value)
              :Varbind(IPADDRESS, "IpAddress"),
	       mData(NULL)
{
  Value(value);
}

IpAddrVarbind::~IpAddrVarbind()
{
  if (mData)
    delete [] mData;
}

const char*
IpAddrVarbind::Printable()
{
  unsigned int size = DataLength();
  mPrintable = new char[size * 2 + 10];
  memset(mPrintable, 0, size*2+10);
  unsigned char* data = mData;

  for (unsigned int index = 0; index < size; index++)
  {
    char number[16];
    memset(number, 0, 16);
#ifdef _WIN32
    sprintf_s(number, 16, "%u", data[index]);
    strcat_s(mPrintable, size*2+10, number);
#else
    sprintf(number, "%u", data[index]);
    strcat(mPrintable, number);
#endif      

    if ((index + 1) < size)
#ifdef _WIN32      
      strcat_s(mPrintable, size*2+10, ".");
#else
      strcat(mPrintable, ".");
#endif
  }
  return mPrintable;
}

void
IpAddrVarbind::Value(char* value)
{
  int length = 4;
  DataLength(length);
  if (mData)
    delete [] mData;
  mData = new unsigned char [length];

#ifdef _WIN32
  char* data = _strdup(value);
#else
  char* data = strdup(value);
#endif
#ifdef _WIN32
  char* strtokContext;
  char* addrByte = strtok_s(data, ".", &strtokContext);
#else
  char* addrByte = strtok(data, ".");
#endif
  int index = 0;

  while (addrByte != NULL)
  {
    mData[index++] = (unsigned char)atoi(addrByte);
#ifdef _WIN32
    addrByte = strtok_s(NULL, ".", &strtokContext);
#else
    addrByte = strtok(NULL, ".");
#endif
  }
  free(data);
}

const char*
IpAddrVarbind::Value()
{
  return Printable();
}

void
IpAddrVarbind::Build(unsigned char*& pdu)
{
  unsigned int len = DataLength();
  *pdu++ = IPADDRESS;
  encodeLength(pdu, (long)len);
  memcpy(pdu, mData, len); 
  pdu += len;
}

unsigned char*
IpAddrVarbind::Data()
{
  unsigned short len = DataLength();
  len += calculateLengthLength(len);
  unsigned char* data = new unsigned char [len + 1];
  unsigned char* retVal = data;
  Build(data);
  return retVal;
}



