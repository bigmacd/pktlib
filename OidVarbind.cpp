

#ifndef __OIDVARBIND_H__
#include "OidVarbind.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

OidVarbind::OidVarbind()
           :Varbind(OID, "OID"),
	    mData(NULL)
{
}

OidVarbind::OidVarbind(unsigned char* &pduPart)
           :Varbind(pduPart, OID, "OID"),
	    mData(NULL)
{
  mData = new unsigned char [DataLength()];
  memcpy(mData, pduPart, DataLength());
  pduPart += DataLength();
}

OidVarbind::OidVarbind(char* string)
           :Varbind(OID, "OID"),
	    mData(NULL)
{
  Value(string);
}

OidVarbind::~OidVarbind()
{
  if (mData != NULL)
    delete [] mData;
}

const char*
OidVarbind::Printable()
{
  if (mPrintable == NULL)
  {
    unsigned int size = DataLength();
    int len =(size * 10) + size;
    mPrintable = new char[len]; 
    memset(mPrintable, 0, len);
    unsigned char* dataStart = mData;
    unsigned char* dataEnd = dataStart + size;
    int index = 0;
    
    while (dataStart < dataEnd)
    {
      if (index == 0)
      {
	unsigned short first;
	unsigned short second;
	::decodeFirstSubId(dataStart,
			   &first,
			   &second);
#ifdef _WIN32
	sprintf_s(mPrintable, len, "%u.%u.", first, second);
#else
	sprintf(mPrintable, "%u.%u.", first, second);
#endif
	index++;
	continue;
      }

      long value = 0;
      ::decodeOID(dataStart, &value);
      char number[16];
      memset(number, 0, 16);
#ifdef _WIN32
      sprintf_s(number, "%u", value);
      strcat_s(mPrintable, len, number);
#else
      sprintf(number, "%lu", value);
      strcat(mPrintable, number);
#endif
      
      if (dataStart < dataEnd)  // there is more
#ifdef _WIN32
	strcat_s(mPrintable, len, ".");
#else
	strcat(mPrintable, ".");
#endif
    }
  }
  return mPrintable;
}

void 
OidVarbind::Value(char* value)
{
  if (mData)
    delete [] mData;
  if (mPrintable)
    delete [] mPrintable;

  unsigned int len = 4096;
  // first use a big buffer until encoded

  //unsigned char* tData = new unsigned char [len];
  unsigned char tData[4096];
  unsigned char* pData = tData;
  unsigned int index = 0;

#ifdef _WIN32
  char* data = _strdup(value);
#else
  char* data = strdup(value);
#endif
  char* strtokContext;
#ifdef _WIN32
  char* oidByte = strtok_s(data, ".", &strtokContext);
  char* secondOidByte = strtok_s(NULL, ".", &strtokContext);
#else
  char* oidByte = strtok(data, ".");
  char* secondOidByte = strtok(NULL, ".");
#endif
  encodeFirstSubId(pData,
		   atoi(oidByte),
		   atoi(secondOidByte));
  len = 1; // first subid encoded above

#ifdef _WIN32
  oidByte = strtok_s(NULL, ".", &strtokContext);  
#else
  oidByte = strtok(NULL, ".");  
#endif
  unsigned int encodedLength;
  while (oidByte != NULL)
  {
    encodeOID(pData, 
	      atoi(oidByte),
	      encodedLength);
    len += encodedLength;
    pData += encodedLength;
#ifdef _WIN32
    oidByte = strtok_s(NULL, ".", &strtokContext);  
#else
    oidByte = strtok(NULL, ".");  
#endif
  }
  free(data);
  mData = new unsigned char [len];
  DataLength(len);
  memcpy(mData, tData, len);
}

const char*
OidVarbind::Value()
{
  return Printable();
}

void
OidVarbind::Build(unsigned char*& pdu)
{
  unsigned int len = DataLength();
  *pdu++ = OID;
  encodeLength(pdu, (long)len);
  memcpy(pdu, mData, len); // the tag too
  pdu += len;
}

unsigned char*
OidVarbind::Data()
{
  unsigned short len = DataLength();
  len += calculateLengthLength(len);
  unsigned char* data = new unsigned char [len + 1];
  unsigned char* retVal = data;
  Build(data);
  return retVal;
}

