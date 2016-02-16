

#ifndef __V1RESPONSEPDU_H__
#define __V1RESPONSEPDU_H__

#ifndef __V1PDU_H__
#include "V1Pdu.h"
#endif

class IntVarbind;


class V1ResponsePdu : public V1Pdu
{
  private:


  protected:



  public:

    V1ResponsePdu();
    ~V1ResponsePdu();
    V1ResponsePdu(const V1ResponsePdu& right);

};
#endif
