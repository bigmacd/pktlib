

#ifndef __SNMPPARSER_H__
#include "SnmpParser.h"
#endif

#if _WIN32
#  include <windows.h>
#endif

#include "SnmpTypes.h"
#include "vbs.h"

//#ifdef DEBUG
//#include <iostream>
//using namespace std;
//#endif


void decodeLength(unsigned char* &pduField, long* value);
void encodeLength(unsigned char* &pduField, long value);

void decodeTag(unsigned char* &pduField, long* value);
void encodeTag(unsigned char* &pduField, long* value);

SnmpParser::SnmpParser(unsigned char* inPdu, unsigned int length)
           :mPacket(NULL),
	    mIown(true)
{
  memset(mErrorMessage, 0, 256);

  unsigned char* inpdu = inPdu;

  long value = 0;  

  if (*inpdu != SEQUENCE)
  {
    sprintf(mErrorMessage, "data does not have starting sequence tag");
    return;
  }

  // skip the SEQUENCE
  ::decodeLength(++inpdu, &value);
  if (value > (long)length)
  {
    // incomplete packet!
    sprintf(mErrorMessage, "incomplete packet (not enough data)");
    return;
  }
  // should value+1 == length?  I think so.

  mPacket = new Packet();

  value = 0;
  ::decodeTag(inpdu, &value);
  if (value == INTEGERTAG)
  {
    IntVarbind* intvb = new IntVarbind(inpdu);
    mPacket->Version(intvb);
  }
  else
  {
    sprintf(mErrorMessage, "could not find version data");
    delete mPacket;
    mPacket = NULL;
    return;
  }

  // get the community string 
  ::decodeTag(inpdu, &value);
  if (value == STRINGTAG)
  {
    StringVarbind* communityvb = new StringVarbind(inpdu);
    mPacket->Community(communityvb);
  }
  else
  {
    sprintf(mErrorMessage, "could not find community string data");
    delete mPacket;
    mPacket = NULL;
    return;
  }

  // next is type indicator
  Pdu* pdu = NULL;
  switch (*inpdu++)
  {
    case V1TRAP:
      pdu = new V1TrapPdu();
      mPacket->pdu(pdu);
      break;

    case V1GETCOMMAND:
      pdu = new V1GetPdu();
      mPacket->pdu(pdu);
      break;

    case V1GETNEXTCOMMAND:
      pdu = new V1GetNextPdu();
      mPacket->pdu(pdu);
      break;

    case V1RESPONSE:
      pdu = new V1ResponsePdu();
      mPacket->pdu(pdu);
      break;

    case V1SETCOMMAND:
      pdu = new V1SetPdu();
      mPacket->pdu(pdu);
      break;

    case V2TRAP:
      pdu = new V2TrapPdu();
      mPacket->pdu(pdu);
      break;

    case INFORMPDU:
      pdu = new InformPdu();
      mPacket->pdu(pdu);
      break;

    case GETBULK:
      pdu = new V2GetBulkPdu();
      mPacket->pdu(pdu);
      break;
      
	default: 
      break;
  }

  if (NULL == pdu)
  {
    sprintf(mErrorMessage, "could not determine PDU type");
    delete mPacket;
    mPacket = NULL;
    return;
  }

  ::decodeLength(inpdu, &value);

  if (mPacket->pdu())
    mPacket->pdu()->Parse(inpdu);
    
  // get all the varbinds
  long totalVarbindLength;
  ::decodeLength(++inpdu, &totalVarbindLength);

  // flags the sequence through a varbind pair
  bool isOID = true;
  //  VbPair* vbpair = new VbPair();
  VbPair* vbpair = NULL;
  unsigned char* endPtr = inpdu + totalVarbindLength;

  while (inpdu < endPtr)
  {

    if (isOID == true)
    {
      // get this varbind pair length
      long value = 0;
      ::decodeLength(++inpdu, &value);
    }

    // get the varbinds
    Varbind* vb = NULL;
    switch (*inpdu++)
    {

      case OID:
      {
        vb = new OidVarbind(inpdu);
        break;
      }

      case INTEGERTAG:
      {
	vb = new IntVarbind(inpdu);
	break;
      }

      case STRINGTAG:
      {
	vb = new StringVarbind(inpdu);
	break;
      }
       
      case IPADDRESS:
      {
	vb = new IpAddrVarbind(inpdu);
	break;
      }
       
      case TIMETICK:
      {
	vb = new TimetickVarbind(inpdu);
	break;
      }
      
      case GAUGE32:
      {
	vb = new GaugeVarbind(inpdu);
	break;
      }

      case COUNTER32:
      {
	vb = new CounterVarbind(inpdu);
	break;
      }

      case COUNTER64:
      {
	vb = new Counter64Varbind(inpdu);
	break;
      }

      //      case SNMPOPAQUE:
      default:
      {
	vb = new OpaqueVarbind(inpdu);
	break;
      }

      //      default:
      //	break;

    } // switch (pdu(*inpdu++])

    if (NULL == vb)
    {
      sprintf(mErrorMessage, "could not determine varbind type");
      delete mPacket;
      mPacket = NULL;
      
      if (NULL != vbpair)
	delete vbpair;

      return;
    }
    
    if (vbpair == NULL)
      vbpair = new VbPair();

    if (isOID)
      vbpair->OIDVarbind((OidVarbind*)vb);
    else
      vbpair->VarBind(vb);
    
    // add to the list    
    if (vbpair->OIDVarbind() != NULL &&
	vbpair->VarBind() != NULL)
    {
      mPacket->Add(vbpair);

      //#ifdef DEBUG
      //      cout << "OID: " << vbpair->OIDVarbind()->Printable() << endl;
      //      cout << "Data: " << vbpair->VarBind()->Printable() << endl;
      //#endif
      vbpair = NULL;
      //      vbpair = new VbPair();
    }

    if (isOID == true)
      isOID = false;
    else
      isOID = true;
  } //  while (inpdu < endPtr)

}
	
SnmpParser::~SnmpParser()
{
  if (mIown == TRUE)
    if (mPacket != NULL)
      delete mPacket;
}

Packet*  
SnmpParser::packet() 
{ 
  mIown = false;
  return mPacket; 
}

void
decodeLength(unsigned char* &pduField, long* value)
{
  if (*pduField & 0x80)
  {
    // get the number of bytes in this length
    unsigned int len = *pduField++ & 0x7f;
    
    // prime the loop
    *value = *pduField++;
    len--;
    for (; len > 0; len--)
    {
      *value <<= 8;
      *value |= *pduField++;
    }
  }
  else
    *value = *pduField++;
}

//#include <iostream.h>
void
encodeLength(unsigned char* &pduField, long value)
{
  if (value < 127) // 127 is reserved
    *pduField++ = (unsigned char)value;
  else
  {
    unsigned short len = 0;
    unsigned int i;
    for (i = 0; i < (sizeof(long)); i++)
    {
      if (value & (0x000000ff << (i*8)))
	//	len++;
	len = (i + 1); // 04/28/03 MAC
    }

    *pduField++ = 0x80 | len;
    int shiftsize = 8 * (len - 1);


    for (i = 0; i < len; i++, shiftsize -= 8)
    {
      *pduField++ = (unsigned char)((value >> shiftsize) & 0x000000ff);
    }
  } 
}

void
decodeTag(unsigned char* &pduField, long* value)
{  
  *value = *pduField & 0x7f;
  if (*pduField & 0x80)
  {
    while (*++pduField & 0x80)
    {
      *value <<= 7;
      *value |= *pduField & 0x7f;
    }
  }
  pduField++;
}

void
encodeTag(unsigned char* &pduField, long* value)
{

}


void
decodeOID(unsigned char* &pduField, long* value)
{
  *value = *pduField & 0x7f;
  while (*pduField & 0x80)
  {
    pduField++;
    *value <<= 7;
    *value |= *pduField & 0x7f;
  }
  pduField++;
}
#if 0
void
encodeOID(unsigned char* newvalue, 
	  int pduField, 
	  unsigned int& encodedLength)
{
  // encode the data in pduField into newvalue 
  // and set encodedLength to number of bytes 
  // placed into newvalue
  int dataIn = pduField;
  if (pduField < 128)
  {
    *newvalue = (unsigned char)pduField;
    encodedLength = 1;
  }
  else
  {
    // find the first non-zero bit
    int bits = (sizeof(int) * 8);
    for (; bits > 0; bits--)
    {
      if (!(pduField & 0x80000000))
	pduField = pduField << 1;
      else
	break;
    }

    // calculate the number of octets needed
    encodedLength = bits / 7;
    if (bits % 7)
      encodedLength++;


    // encode
    int totalBits = (sizeof(int) * 8);
    int shiftpad = (encodedLength * 7) % bits;
    pduField = dataIn << (totalBits - (bits + shiftpad));
    for (unsigned int i = encodedLength; i > 0; i--)
    {
      int shiftsize = 7;
      *newvalue = 0;
      *newvalue = (pduField & 0xfe000000) >> 25;

      if (i > 1)
	*newvalue |= 0x80;

      newvalue++;

      pduField = pduField << shiftsize;
    }
  }
}
#endif

#include <iostream>
using namespace std;

void
encodeOID(unsigned char* newvalue, 
	  int pduField, 
	  unsigned int& encodedLength)
{
  //  cout << "in encodeOID" << endl;
  // encode the data in pduField into newvalue 
  // and set encodedLength to number of bytes 
  // placed into newvalue
  int dataIn = pduField;
  int d2 = pduField;
  if (pduField < 128)
  {
    *newvalue = (unsigned char)pduField;
    encodedLength = 1;
  }
  else
  {
    /////////////////////// debug only
    //    for (int i = 0; i < 32; i++)
    //    {
    //      if (dataIn & 0x00000001)
    //      {
    //	cout << "1";
    //      }
    //      else 
    //      {
    //	cout << "0";
    //      }
    //      dataIn = dataIn >> 1;
    //    }
    //    cout << endl;
    ////////////////////////

    // find the first non-zero bit
    int bits = (sizeof(int) * 8);
    //    cout << "bits is " << bits << endl;
    for (; bits > 0; bits--)
    {
      if (!(pduField & 0x80000000))
	pduField = pduField << 1;
      else
	break;
    }
    //    cout << "now bits is " << bits << endl;

    // calculate the number of octets needed
    encodedLength = bits / 7;
    if (bits % 7)
      encodedLength++;

    //    cout << "encodedlength is " << encodedLength << endl;
    // roll the incoming value to remove leading zeros
    //    int rollbits = (sizeof(int) * 8) - bits;
    //    pduField >> rollbits;
    //    cout << "rollbits is " << rollbits << endl;

    // now we know how many sub identifiers are needs
    // and all the data is toward the left of pduField
    unsigned char* subs = new unsigned char[encodedLength];
    for (unsigned int subIds = 1; subIds <= encodedLength; subIds++)
    {
      subs[subIds-1] = 0;

      int setbit = 0x00;  // the last subid the upper bit is off
      if (subIds != 1)
	setbit = 0x80;    // not the last subid the upper bit is on

      // take 7 bits at a time, shifting right 7 bits.
      //      printf("pdufield is %d\n", d2);
      //      printf("subids is %d\n", subIds);
      //      unsigned char t = (pduField >> (7 * (subIds - 1))) & 0x7f;
      int t = (d2 >> (7 * (subIds - 1))) & 0x0000007f;
      //      printf("t is %d\n", t);
      unsigned char subvalue = t;

      subvalue |= setbit; // fix the upper bit.

      subs[subIds - 1] = subvalue;
    }

    // now flip the order of the encoded subids and place in passed in pointer.
    for (int subIds2 = (encodedLength - 1); subIds2 >= 0; subIds2--)
    {
      *newvalue++ = subs[subIds2];
    }

    // ugh, did I really forget to delete this in version 2.98.79
    if (subs)
      delete [] subs;
  }
}

// for general length determinations
unsigned int
calculateLengthLength(unsigned int len)
{
  unsigned int lenLength = 0;
  unsigned int i;
  for (i = 0; i < (sizeof(long)); i++)
  {
    if (len & (0x000000ff << (i*8)))
      lenLength++;
  }
  if (lenLength > 1) // for the length byte
    lenLength++;
  
  int ii = sizeof(long);
  ii--;
  for (; ii >= 0; ii--)
  {
    if (len & (0x000000ff << (ii*8)))
    {
      if (len & (0x00000080 << (ii*8)))
	lenLength++;
      break;
    }
  }  
  return lenLength;
}

// for total length calculations (packet and varbindlist)
unsigned int
calculateTotalLengthLength(unsigned int len)
{
  if (len < 127) // 127 is reserved
    return 1;
  else
  {
    unsigned short lenLen = 0;
    for (unsigned int i = 0; i < (sizeof(long)); i++)
    {
      if (len & (0x000000ff << (i*8)))
	lenLen++;
    }
    return ++lenLen; // the 0x8X octet
  } 
}

void
decodeFirstSubId(unsigned char* &pduField,
		 unsigned short* first,		       
		 unsigned short* second)
{
  if (*pduField < 40)
  {
    *first = 0;
    *second = *pduField++;
  }
  else
    if (*pduField < 80)
    {
      *first = 1;
      *second = ((*pduField++) - 40);
    }
    else
    {
      *first = 2;
      *second = ((*pduField++) - 80);
    }
}		       

void
encodeFirstSubId(unsigned char* &pduField,
		 int first,		       
		 int second)
{
  *pduField++ = (first * 40) + second;
}

