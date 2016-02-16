

#ifndef __V1PDU_H__
#include "V1Pdu.h"
#endif

#ifndef __INTVARBIND_H__
#include "IntVarbind.h"
#endif

#include "SnmpTypes.h"
#include <time.h>

V1Pdu::V1Pdu()
      :mRequestIdVb(NULL),
       mErrorStatusVb(NULL),
       mErrorIndexVb(NULL)
{
  mRequestIdVb = new IntVarbind(time(0));
  mErrorStatusVb = new IntVarbind(0);
  mErrorIndexVb = new IntVarbind(0);
}

V1Pdu::~V1Pdu()
{
  if (mRequestIdVb)
    delete mRequestIdVb;

  if (mErrorStatusVb)
    delete mErrorStatusVb;

  if (mErrorIndexVb)
    delete mErrorIndexVb;

}


V1Pdu::V1Pdu(const V1Pdu& right)
{

}

int              
V1Pdu::RequestId()
{
  if (mRequestIdVb)
    return mRequestIdVb->Value();
  else
    return 0;
}

void             
V1Pdu::RequestId(int value)
{
  if (mRequestIdVb)
    delete mRequestIdVb;
  mRequestIdVb = new IntVarbind(value);
}

int              
V1Pdu::ErrorIndex()
{
  if (mErrorIndexVb)
    return mErrorIndexVb->Value();
  else
    return 0;
}

void             
V1Pdu::ErrorIndex(int value)
{
  if (mErrorIndexVb)
    delete mErrorIndexVb;
  mErrorIndexVb = new IntVarbind(value);
}

int              
V1Pdu::ErrorStatus()
{
  if (mErrorStatusVb)
    return mErrorStatusVb->Value();
  else
    return 0;
}

void             
V1Pdu::ErrorStatus(int value)
{
  if (mErrorStatusVb)
    delete mErrorStatusVb;
  mErrorStatusVb = new IntVarbind(value);
}

void             
V1Pdu::Parse(unsigned char* &pdu)
{
  long value = 0;

  // next is request id
  ::decodeTag(pdu, &value);
  if (value == INTEGERTAG)
  {
    if (mRequestIdVb)
      delete mRequestIdVb;
    mRequestIdVb = new IntVarbind(pdu);
  }

  // next is error status
  ::decodeTag(pdu, &value);
  if (value == INTEGERTAG)
  {
    if (mErrorStatusVb)
      delete mErrorStatusVb;
    mErrorStatusVb = new IntVarbind(pdu);
  }

  // next is error index
  ::decodeTag(pdu, &value);
  if (value == INTEGERTAG)
  {
    if (mErrorIndexVb)
      delete mErrorIndexVb;
    mErrorIndexVb = new IntVarbind(pdu);
  }
}

void             
V1Pdu::Build(unsigned char*& pdu)
{
  if (mRequestIdVb != NULL)
    mRequestIdVb->Build(pdu);

  if (mErrorStatusVb != NULL)
    mErrorStatusVb->Build(pdu);

  if (mErrorIndexVb != NULL)
    mErrorIndexVb->Build(pdu);

}

unsigned int     
V1Pdu::Length()
{
  unsigned int len = 0;

  if (mRequestIdVb != NULL)
    len += mRequestIdVb->Length();

  if (mErrorStatusVb != NULL)
    len += mErrorStatusVb->Length();

  if (mErrorIndexVb != NULL)
    len += mErrorIndexVb->Length();

  return len;
}

void             
V1Pdu::MakeResponsePdu()
{
  mType = V1RESPONSE;
}
