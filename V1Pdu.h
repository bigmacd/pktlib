

#ifndef __V1PDU_H__
#define __V1PDU_H__

#ifndef __PDU_H__
#include "Pdu.h"
#endif

class IntVarbind;


class V1Pdu : public Pdu
{
  private:

    IntVarbind*      mRequestIdVb;
    IntVarbind*      mErrorStatusVb;
    IntVarbind*      mErrorIndexVb;


  protected:

    unsigned char    mType;

  public:

    V1Pdu();
    virtual ~V1Pdu();
    V1Pdu(const V1Pdu& right);

    virtual int              RequestId();
    virtual void             RequestId(int value);

    virtual int              ErrorIndex();
    virtual void             ErrorIndex(int value);

    virtual int              ErrorStatus();
    virtual void             ErrorStatus(int value);

    virtual void             Parse(unsigned char*& buffer);

    virtual void             Build(unsigned char*& pdu);
    virtual unsigned int     Length();

    virtual void             MakeResponsePdu();

    virtual unsigned char    Type() { return mType; }

    // in case we want to know from whence it came
    virtual const char*      SenderIP()  { return 0L; }

};
#endif
