

#ifndef __V1SETPDU_H__
#include "V1SetPdu.h"
#endif

#include "SnmpTypes.h"

V1SetPdu::V1SetPdu()
{
  mType = V1SETCOMMAND;
}

V1SetPdu::~V1SetPdu()
{

}

V1SetPdu::V1SetPdu(const V1SetPdu& right)
{
  mType = right.mType;
}

