

#ifndef __TIMETICKVARBIND_H__
#include "TimeTickVarbind.h"
#endif

TimetickVarbind::TimetickVarbind()
                :ScalarVarbind(TIMETICK, "TimeTick")
{
}

TimetickVarbind::TimetickVarbind(unsigned char* &pduPart)
                :ScalarVarbind(pduPart, TIMETICK, "TimeTick")
{
  mValue = ::ComputeLongValue(pduPart, DataLength());
}

TimetickVarbind::TimetickVarbind(unsigned long timetick)
                :ScalarVarbind(TIMETICK, "TimeTick")
{
  ScalarVarbind::Value(timetick);
}

TimetickVarbind::~TimetickVarbind()
{
}

void
TimetickVarbind::Build(unsigned char*& pdu)
{
  *pdu++ = TIMETICK;
  ScalarVarbind::Build(pdu);
}

