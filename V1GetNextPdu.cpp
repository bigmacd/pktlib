

#ifndef __V1GETNEXTPDU_H__
#include "V1GetNextPdu.h"
#endif

#include "SnmpTypes.h"

V1GetNextPdu::V1GetNextPdu()
{
  mType = V1GETNEXTCOMMAND;
}

V1GetNextPdu::~V1GetNextPdu()
{

}

V1GetNextPdu::V1GetNextPdu(const V1GetNextPdu& right)

{
  mType = right.mType;
}
