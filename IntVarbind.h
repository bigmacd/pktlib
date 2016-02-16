

#ifndef __INTVARBIND_H__
#define __INTVARBIND_H__

#ifndef __SCALARVARBIND_H__
#include "ScalarVarbind.h"
#endif

#include "SnmpTypes.h"

unsigned int  ComputeIntValue(unsigned char* &pduPart);
unsigned long ComputeLongValue(unsigned char* &pduPart);

class IntVarbind : public ScalarVarbind
{
  private:



  protected:



  public:
    
    IntVarbind();
    IntVarbind(unsigned char* &pduPart);
    IntVarbind(int value);
    ~IntVarbind();

    virtual void              Build(unsigned char*& pdu);
};
#endif
