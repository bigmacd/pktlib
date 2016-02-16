

#ifndef __V2GETBULKPDU_H__
#include "V2GetBulkPdu.h"
#endif

#include "SnmpTypes.h"

V2GetBulkPdu::V2GetBulkPdu()
{
  mType = GETBULK;
}

V2GetBulkPdu::~V2GetBulkPdu()
{

}

V2GetBulkPdu::V2GetBulkPdu(const V2GetBulkPdu& right)

{
  mType = right.mType;
}

int      
V2GetBulkPdu::NonRepeaters()
{
  return ErrorStatus();
}

void     
V2GetBulkPdu::NonRepeaters(int value)
{
  ErrorStatus(value);
}

int      
V2GetBulkPdu::MaxRepetitions()
{
  return ErrorIndex();  
}

void     
V2GetBulkPdu::MaxRepetitions(int value)
{
  ErrorIndex(value);
}


