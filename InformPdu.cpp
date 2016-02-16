#ifndef __INFORMPDU_H__
#include "InformPdu.h"
#endif

#include "SnmpTypes.h"

InformPdu::InformPdu()
          :V2Notification()
{
  mType = INFORMPDU;
}

InformPdu::~InformPdu()
{

}

InformPdu::InformPdu(const InformPdu& right)

{
  mType = right.mType;
}



