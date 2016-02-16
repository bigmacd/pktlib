

#ifndef __V1GETPDU_H__
#define __V1GETPDU_H__

#ifndef __V1PDU_H__
#include "V1Pdu.h"
#endif

class IntVarbind;


class V1GetPdu : public V1Pdu
{
  private:


  protected:



  public:

    V1GetPdu();
    ~V1GetPdu();
    V1GetPdu(const V1GetPdu& right);

};
#endif
