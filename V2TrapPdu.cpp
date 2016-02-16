

#ifndef __V2TRAPPDU_H__
#include "V2TrapPdu.h"
#endif

#include "SnmpTypes.h"
#include "VarbindList.h"
#include "OidVarbind.h"
#include "CounterVarbind.h"

V2TrapPdu::V2TrapPdu()  
          :V2Notification()
{
  mType = V2TRAP;
}

V2TrapPdu::~V2TrapPdu()
{

}

V2TrapPdu::V2TrapPdu(const V2TrapPdu& right)
{
  mType = right.mType;
}








