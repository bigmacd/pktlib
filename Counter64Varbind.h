

#ifndef __COUNTER64VARBIND_H__
#define __COUNTER64VARBIND_H__

#ifndef __SCALAR64VARBIND_H__
#include "Scalar64Varbind.h"
#endif

#include "Build.h"
#include "SnmpTypes.h"

class Counter64Varbind : public Scalar64Varbind
{
  private:


  protected:



  public:
    
    Counter64Varbind();
    Counter64Varbind(unsigned char* &pduPart);
    Counter64Varbind(__int64 counter);
    ~Counter64Varbind();

    virtual void            Build(unsigned char*& pdu);
};
#endif
