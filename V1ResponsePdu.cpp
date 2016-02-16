

#ifndef __V1RESPONSEPDU_H__
#include "V1ResponsePdu.h"
#endif

#include "SnmpTypes.h"

V1ResponsePdu::V1ResponsePdu()
{
  mType = V1RESPONSE;
}

V1ResponsePdu::~V1ResponsePdu()
{

}

V1ResponsePdu::V1ResponsePdu(const V1ResponsePdu& right)

{
  mType = right.mType;
}
