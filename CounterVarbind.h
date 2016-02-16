

#ifndef __COUNTERVARBIND_H__
#define __COUNTERVARBIND_H__

#ifndef __SCALARVARBIND_H__
#include "ScalarVarbind.h"
#endif

#include "Build.h"
#include "SnmpTypes.h"

class CounterVarbind : public ScalarVarbind
{
  private:


  protected:



  public:
    
    CounterVarbind();
    CounterVarbind(unsigned char* &pduPart);
    CounterVarbind(unsigned long counter);
    ~CounterVarbind();

    virtual void            Build(unsigned char*& pdu);
};
#endif
