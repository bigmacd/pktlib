

#ifndef __STRINGVARBIND_H__
#include "StringVarbind.h"
#endif

#ifndef __COMPAT_H__
#include "compat.h"
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include "string.h"

#if defined(_LINUX) || defined(_IRIX) || defined(_SOLARIS) || defined(_FREEBSD)
#include <ctype.h>
#endif

#ifdef _HPUX
#include <ctype.h>
#endif

StringVarbind::StringVarbind()
              :Varbind(STRINGTAG, "String"),
	       mData(NULL),
	       mHexData(FALSE)
{

}

StringVarbind::StringVarbind(unsigned char* &pduPart)
              :Varbind(pduPart, STRINGTAG, "String"),
	       mData(NULL),
	       mHexData(FALSE)
{
  bool nullString = false;
  // added to handle null strings? - MAC 12/5/06
  if (DataLength() == 0) 
  {
    DataLength(1);
    nullString = true;
  }
  // end of addition

  mData = new unsigned char [DataLength()];
  memset(mData, 0, DataLength());
  if (!nullString)
  {
    memcpy(mData, pduPart, DataLength());
    pduPart += DataLength();
  }
}

StringVarbind::StringVarbind(char* string)
              :Varbind(STRINGTAG, "String"),
	       mData(NULL),
	       mHexData(FALSE)
{
  int length = strlen(string);
  // added to handle null strings? - MAC 12/5/06
  if (length == 0) length = 1;
  // end of addition
  DataLength(length);
  mData = new unsigned char [length];
  memcpy(mData, string, length);
}

StringVarbind::StringVarbind(char* string, int len)
              :Varbind(STRINGTAG, "OctetString"),
	       mData(NULL),
	       mHexData(TRUE)
{
  // expect the data coming in to look like this:
  // 0x0123456789
  char* t = strchr(string, 'x');
  int length = strlen(t);
  length--; // skip the "0x" part of the input

  bool wasOdd = FALSE;

  if (t != NULL)
  {
    if (length % 2) // odd number of digits
    {
      wasOdd = TRUE;
      *t = '0'; // borrow this spot, the 'x' of "0x"
      length++;
    }
    else
      t++;

    DataLength(length/2);
    mData = new unsigned char [length/2];

    for (int x = 0, index = 0; x < length; x+=2, index++)
    {
      mData[index] = 0;
      for (int y = 0; y < 2; y++)
      {
	// if input char is a number
	if (t[x+y] >= '0' && t[x+y] <= '9')
	{
	  // subtrace decimal 30 ('0' - 30 = 0, '9' - 30 = 9)
	  mData[index] += ((t[x+y] - 0x30) << (4 * (1 - y)));
	}
	else
	  // if input char is a hex number lower case
	  if (t[x+y] >= 'a' && t[x+y] <= 'f')
	  {
	    // subtrace decimal 87 ('a' - 87 = 10, 'f' - 87 = 15)
	    mData[index] += ((t[x+y] - 87) << (4 * (1 - y)));
	  }
	  else
	    // if input char is a hex number upper case
	    if (t[x+y] >= 'A' && t[x+y] <= 'F')
	    {
	      // subtrace decimal 55 ('A' - 55 = 10, 'F' - 55 = 15)
	      mData[index] += ((t[x+y] - 55) << (4 * (1 - y)));
	    }
      }
    }
    if (wasOdd)
      *t = 'x';  // restore the value
  } // if (t != NULL)
}

StringVarbind::~StringVarbind()
{
  if (mData)
    delete [] mData;
}

const char*
StringVarbind::Printable()
{
  if (mPrintable == NULL)
  {
    int size = DataLength();
    int i = 0;
    for(i = 0; i < size; i++)
    {
      if ((mData[i] != '\r')&& 
	  (mData[i] != '\n')&&
	  (mData[i] != '\t')&&
	  (isprint((int)(mData[i])) == 0))
      {
	mHexData = TRUE;
	break;
      }
    }

    // support the null terminated string
    if ((i + 1) == size && mData[i] == 0)
      mHexData = FALSE;

    if (mHexData)
    {
      mPrintable = new char[(size*2) + 1];
      memset(mPrintable, 0, (size*2) + 1);
      for (int x = 0; x < size; x++)
      {
	char c[10];
#ifdef _WIN32
	sprintf_s(c, 10, "%02x", mData[x]);
	strcat_s(mPrintable, size*2 + 1, c);
#else
	sprintf(c, "%02x", mData[x]);
	strcat(mPrintable, c);
#endif
      }
    }
    else
    {
      mPrintable = new char[size + 1];
      memcpy(mPrintable, mData, size);
      mPrintable[size] = '\0';
    }
  }
  return mPrintable;
}

void
StringVarbind::Build(unsigned char*& pdu)
{
  unsigned int len = DataLength();
  *pdu++ = STRINGTAG;
  encodeLength(pdu, (long)len);
  memcpy(pdu, mData, len); 
  pdu += len;
}

unsigned char* 
StringVarbind::Data()
{
  unsigned short len = DataLength();
  len += calculateLengthLength(len);
  if (len == 0) len = 1; // for a single null character  - MAC 12/5/06
  unsigned char* data = new unsigned char [len + 1];
  unsigned char* retVal = data;
  Build(data);
  return retVal;
}

const char*   
StringVarbind::Value()
{
  return Printable();
}
