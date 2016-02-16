

#ifndef __OIDVARBIND_H__
#define __OIDVARBIND_H__

#ifndef __VARBIND_H__
#include "Varbind.h"
#endif

#include "SnmpTypes.h"

class OidVarbind : public Varbind
{
  private:

    unsigned char*    mData;

  protected:



  public:
    
    OidVarbind();
    OidVarbind(unsigned char* &pduPart);
    OidVarbind(char* string);
    ~OidVarbind();
  
    void                   Value(char* value);
    const char*            Value();
    virtual const char*    Printable();

    virtual void           Build(unsigned char*& pdu);
    virtual unsigned char* Data();
};
#endif
