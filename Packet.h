

#ifndef __PACKET_H__
#define __PACKET_H__

#include "SnmpTypes.h"
#include "GenericPacket.h"

class StringVarbind;
class IntVarbind;
class Pdu;
class VarbindList;
class VbPair;

class Packet : public GenericPacket
{

  private:

    StringVarbind*   mCommunityVb;
    IntVarbind*      mVersionVb;
    unsigned int     mType;

    Pdu*             mPdu;

    VarbindList*     mVbList;

    VbPair*          GetVbNumber(int which);

    long             mRealIp;

  protected:



  public:

    Packet();
    Packet(unsigned int type, unsigned int version = VERSIONV1);
    Packet(const Packet& right);

    ~Packet();

    const char*            PktLibVersion(); 

    void                   Type(unsigned int type);

    virtual int            Version();
    void                   Version(int version);
    void                   Version(IntVarbind* intvb);

    unsigned int           Length();
    virtual unsigned int   TotalLength();

    virtual const char*    Community(); 
    void                   Community(const char* community);
    void                   Community(StringVarbind* community);

    virtual int            VbListLength();
    virtual const char*    VbOID(int which);
    virtual const char*    VbType(int which);
    virtual const char*    VbData(int which);

    const char*            RealIp();
    void                   RealIp(struct sockaddr_in* peer);

    VarbindList*   VbList();
    void           VbList(VarbindList* vblist);

    Pdu*           pdu();
    void           pdu(Pdu* inPdu);

    Packet*        Next;

    void           Add(VbPair* vbpair);

    virtual void   Build(unsigned char*& pdu);

    virtual void   AddV2TrapVarbinds(unsigned long counterValue,
				     char* trapOidValue,
				     int specificType = 6,
				     int genericType = 1,
				     bool noSubIds = false );
    

    // from the pdu interface
    virtual int                RequestId();
    virtual void               RequestId(int value);

    virtual int                ErrorIndex();
    virtual void               ErrorIndex(int value);

    virtual int                ErrorStatus();
    virtual void               ErrorStatus(int value);

    virtual int                GenericTrapType();
    virtual void               GenericTrapType(int value);

    virtual int                SpecificTrapType();
    virtual void               SpecificTrapType(int value);

    virtual unsigned long      TimeTicks();
    virtual void               TimeTicks(unsigned long value);

    virtual const char*        SenderIP();
    virtual void               SenderIP(const char* value);

    virtual const char*        SenderOID();
    virtual void               SenderOID(const char* value);

    virtual unsigned char      Type();
    
};

#endif

