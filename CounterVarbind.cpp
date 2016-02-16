

#ifndef __COUNTERVARBIND_H__
#  include "CounterVarbind.h"
#endif

#if _WIN32
#  include <windows.h>
#  include <memory.h>
#else
#include <stdlib.h>
#endif

CounterVarbind::CounterVarbind()
               :ScalarVarbind(COUNTER32, "Counter")
{

}

CounterVarbind::CounterVarbind(unsigned char* &pduPart)
               :ScalarVarbind(pduPart, COUNTER32, "Counter")
{
  mValue = ::ComputeLongValue(pduPart, DataLength());
}

CounterVarbind::CounterVarbind(unsigned long value)
               :ScalarVarbind(COUNTER32, "Counter")
{
  if (value < 0)
    value = (unsigned long)abs((long)value);
  ScalarVarbind::Value(value);
}

CounterVarbind::~CounterVarbind()
{
}

void
CounterVarbind::Build(unsigned char*& pdu)
{
  *pdu++ = COUNTER32;
  ScalarVarbind::Build(pdu);
}

