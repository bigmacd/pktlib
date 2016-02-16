

#ifndef __IPADDRVARBIND_H__
#define __IPADDRVARBIND_H__

#ifndef __VARBIND_H__
#include "Varbind.h"
#endif

#include "SnmpTypes.h"

class IpAddrVarbind : public Varbind
{
  private:

    unsigned char*           mData;

  protected:



  public:
    
    IpAddrVarbind();
    IpAddrVarbind(unsigned char* &pduPart);
    IpAddrVarbind(char* ipaddr);
    ~IpAddrVarbind();

    void                   Value(char* value);
    const char*            Value();
    virtual const char*    Printable();

    virtual void           Build(unsigned char*& pdu);
    virtual unsigned char* Data();

};
#endif


