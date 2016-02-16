
#ifndef __COUNTER64VARBIND_H__
#  include "Counter64Varbind.h"
#endif

#if _WIN32
#  include <windows.h>
#  include <memory.h>
#endif

Counter64Varbind::Counter64Varbind()
                 :Scalar64Varbind(COUNTER64, "Counter64")
{

}

Counter64Varbind::Counter64Varbind(unsigned char* &pduPart)
                 :Scalar64Varbind(pduPart, COUNTER64, "Counter64")
{
  mValue = ::Compute64Value(pduPart, DataLength());
}

Counter64Varbind::Counter64Varbind(__int64 value)
                 :Scalar64Varbind(COUNTER64, "Counter64")
{
  // this is the abs function (see CounterVarbind.cpp)
  if (value < 0)
    value = (~value) + 1;
  Scalar64Varbind::Value(value);
}

Counter64Varbind::~Counter64Varbind()
{
}

void
Counter64Varbind::Build(unsigned char*& pdu)
{
  *pdu++ = COUNTER64;
  Scalar64Varbind::Build(pdu);
}
