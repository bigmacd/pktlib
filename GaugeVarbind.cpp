

#ifndef __GAUGEVARBIND_H__
#include "GaugeVarbind.h"
#endif

GaugeVarbind::GaugeVarbind()
             :ScalarVarbind(GAUGE32, "Gauge")
{
}

GaugeVarbind::GaugeVarbind(unsigned char* &pduPart)
             :ScalarVarbind(pduPart, GAUGE32, "Gauge")
{
  mValue = ::ComputeLongValue(pduPart, DataLength());
}

GaugeVarbind::GaugeVarbind(unsigned long value)
             :ScalarVarbind(GAUGE32, "Gauge")
{
  ScalarVarbind::Value(value);
}

GaugeVarbind::~GaugeVarbind()
{
}

void
GaugeVarbind::Build(unsigned char*& pdu)
{
  *pdu++ = GAUGE32;
  ScalarVarbind::Build(pdu);
}


