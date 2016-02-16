

#ifndef __TRAPPDU_H__
#define __TRAPPDU_H__

#ifndef __PDU_H__
#include "Pdu.h"
#endif

#include "SnmpTypes.h"

class IntVarbind;
class TimetickVarbind;
class OidVarbind;
class IpVarbind;
class IpAddrVarbind;

class V1TrapPdu : public Pdu
{
  private:

    IntVarbind*      mGenericTypeVb;
    IntVarbind*      mSpecificTypeVb;
    TimetickVarbind* mTimeStampVb;
    OidVarbind*      mOidVb;
    IpAddrVarbind*   mIpAddrVb;

  protected:



  public:

    V1TrapPdu();
    ~V1TrapPdu();
    V1TrapPdu(const V1TrapPdu& right);

    virtual int              GenericTrapType();
    virtual void             GenericTrapType(int value);

    virtual int              SpecificTrapType();
    virtual void             SpecificTrapType(int value);

    virtual unsigned long    TimeTicks();
    virtual void             TimeTicks(unsigned long value);

    virtual const char*      SenderOID();
    virtual void             SenderOID(const char* value);

    virtual const char*      SenderIP();
    virtual void             SenderIP(const char* value);

    virtual void             Parse(unsigned char* &buffer);

    virtual void             Build(unsigned char*& pdu);
    virtual unsigned int     Length();

    virtual unsigned char    Type() { return V1TRAP; }
  
};
#endif

