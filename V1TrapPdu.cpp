

#ifndef __V1TRAPPDU_H__
#include "V1TrapPdu.h"
#endif

#include "vbTypes.h"

V1TrapPdu::V1TrapPdu()
        :mGenericTypeVb(NULL),
	 mSpecificTypeVb(NULL),
	 mTimeStampVb(NULL),
	 mIpAddrVb(NULL),
	 mOidVb(NULL)
{

}

V1TrapPdu::V1TrapPdu(const V1TrapPdu& right)
{

}

V1TrapPdu::~V1TrapPdu()
{
  if (mGenericTypeVb)
	delete mGenericTypeVb;
  if (mSpecificTypeVb)
	delete mSpecificTypeVb;
  if (mTimeStampVb)
	delete mTimeStampVb;
  if (mIpAddrVb)
	delete mIpAddrVb;
  if (mOidVb)
	delete mOidVb;
}

#if 0
void             
V1TrapPdu::GenericTrapType(IntVarbind* Gtype)
{
  if (mGenericTypeVb)
	delete mGenericTypeVb;
  mGenericTypeVb = Gtype;
}

void             
V1TrapPdu::SpecificTrapType(IntVarbind* Stype)
{
  if (mSpecificTypeVb)
	delete mSpecificTypeVb;
  mSpecificTypeVb = Stype;
}

void             
V1TrapPdu::TimeTicks(TimetickVarbind* timestamp)
{
  if (mTimeStampVb)
	delete mTimeStampVb;
  mTimeStampVb = timestamp;
}

void             
V1TrapPdu::SenderOID(OidVarbind* vb)
{
  if (mOidVb)
	delete mOidVb;
  mOidVb = vb;
}

void             
V1TrapPdu::SenderIP(IpAddrVarbind* vb)
{
  if (mIpAddrVb)
	delete mIpAddrVb;
  mIpAddrVb = vb;
}
#endif

void 
V1TrapPdu::Parse(unsigned char* &pdu)
{
  long value = 0;

  // next is OID of sender
  ::decodeTag(pdu, &value);
  if (value == OID)
    mOidVb = new OidVarbind(pdu);

  // next is ipaddr of sender
  ::decodeTag(pdu, &value);
  if (value == IPADDRESS)
    mIpAddrVb = new IpAddrVarbind(pdu);

  // next is trap type
  ::decodeTag(pdu, &value);
  if (value == INTEGERTAG)
    mGenericTypeVb = new IntVarbind(pdu);

  // next is specific type
  ::decodeTag(pdu, &value);
  if (value == INTEGERTAG)
    mSpecificTypeVb = new IntVarbind(pdu);

  // next is timestamp
  ::decodeTag(pdu, &value);
  if (value == TIMETICK)
    mTimeStampVb = new TimetickVarbind(pdu);

}

const char*
V1TrapPdu::SenderOID()
{
  if (mOidVb)
    return (const char*)(mOidVb->Value());
  else
    return NULL;
}

void
V1TrapPdu::SenderOID(const char* value)
{
  if (mOidVb)
    delete mOidVb;
  mOidVb = new OidVarbind((char*)value);
}

const char*
V1TrapPdu::SenderIP()
{
  if (mIpAddrVb)
    return mIpAddrVb->Value();
  else
    return NULL;
}

void
V1TrapPdu::SenderIP(const char* value)
{
  if (mIpAddrVb)
    delete mIpAddrVb;
  mIpAddrVb = new IpAddrVarbind((char*)value);
}

unsigned long
V1TrapPdu::TimeTicks()
{
  if (mTimeStampVb)
    return mTimeStampVb->Value();
  else
    return 0;
}

void
V1TrapPdu::TimeTicks(unsigned long value)
{
  if (mTimeStampVb)
    delete mTimeStampVb;
  mTimeStampVb = new TimetickVarbind(value);
}

int
V1TrapPdu::SpecificTrapType()
{
  if (mSpecificTypeVb)
    return mSpecificTypeVb->Value();
  else
    return 0;
}

void
V1TrapPdu::SpecificTrapType(int value)
{
    if (mSpecificTypeVb)
	delete mSpecificTypeVb;
    mSpecificTypeVb = new IntVarbind(value);
}

int 
V1TrapPdu::GenericTrapType()
{
  if (mGenericTypeVb)
    return mGenericTypeVb->Value();
  else
    return 0;
}

void
V1TrapPdu::GenericTrapType(int value)
{
  if (mGenericTypeVb)
	delete mGenericTypeVb;
  mGenericTypeVb = new IntVarbind(value);
}

void
V1TrapPdu::Build(unsigned char*& pdu)
{
  if (mOidVb != NULL)
    mOidVb->Build(pdu);
  if (mIpAddrVb != NULL)
    mIpAddrVb->Build(pdu);
  if (mGenericTypeVb != NULL)
    mGenericTypeVb->Build(pdu);
  if (mSpecificTypeVb != NULL)
    mSpecificTypeVb->Build(pdu);
  if (mTimeStampVb != NULL)
    mTimeStampVb->Build(pdu);
}

unsigned int
V1TrapPdu::Length()
{
  unsigned int len = 0;

  if (mOidVb != NULL)
    len += mOidVb->Length();

  if (mIpAddrVb != NULL)
    len += mIpAddrVb->Length();
  
  if (mGenericTypeVb != NULL)
    len += mGenericTypeVb->Length();

  if (mSpecificTypeVb != NULL)
    len += mSpecificTypeVb->Length();

  if (mTimeStampVb != NULL)
    len += mTimeStampVb->Length();

  return len;
}
