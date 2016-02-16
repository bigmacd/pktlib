

#ifndef __V1GETNEXTPDU_H__
#define __V1GETNEXTPDU_H__

#ifndef __V1PDU_H__
#include "V1Pdu.h"
#endif

class IntVarbind;


class V1GetNextPdu : public V1Pdu
{
  private:


  protected:



  public:

    V1GetNextPdu();
    ~V1GetNextPdu();
    V1GetNextPdu(const V1GetNextPdu& right);

};
#endif
