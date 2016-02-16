

#ifndef __GAUGEVARBIND_H__
#define __GAUGEVARBIND_H__

#ifndef __SCALARVARBIND_H__
#include "ScalarVarbind.h"
#endif

#include "SnmpTypes.h"

class GaugeVarbind : public ScalarVarbind
{
  private:

   

  protected:



  public:
    
    GaugeVarbind();
    GaugeVarbind(unsigned char* &pduPart);
    GaugeVarbind(unsigned long value);
    ~GaugeVarbind();

    virtual void             Build(unsigned char*& pdu);
};
#endif
