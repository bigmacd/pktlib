#ifndef __INTVARBIND_H__
#include "IntVarbind.h"
#endif

IntVarbind::IntVarbind()
           :ScalarVarbind(INTEGERTAG, "Integer")
{
}

IntVarbind::IntVarbind(unsigned char* &pduPart)
           :ScalarVarbind(pduPart, INTEGERTAG, "Integer")
{
  mValue = ComputeIntValue(pduPart, DataLength());
}

IntVarbind::IntVarbind(int value)
           :ScalarVarbind(INTEGERTAG, "Integer")
{
  // calculate the minimum length for the current value
  ScalarVarbind::Value(value);
}


IntVarbind::~IntVarbind()
{
}

void
IntVarbind::Build(unsigned char*& pdu)
{
  *pdu++ = INTEGERTAG;
  ScalarVarbind::Build(pdu);
}


