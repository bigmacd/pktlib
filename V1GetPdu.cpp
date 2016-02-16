

#ifndef __V1GETPDU_H__
#include "V1GetPdu.h"
#endif

#include "SnmpTypes.h"

V1GetPdu::V1GetPdu()
{
  mType = V1GETCOMMAND;
}

V1GetPdu::~V1GetPdu()
{

}

V1GetPdu::V1GetPdu(const V1GetPdu& right)

{
  mType = right.mType;
}



