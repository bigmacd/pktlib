

#ifndef __V2GETBULKPDU_H__
#define __V2GETBULKPDU_H__

#ifndef __V1PDU_H__
#include "V1Pdu.h"
#endif


class V2GetBulkPdu : public V1Pdu
{
  private:


  protected:



  public:

    V2GetBulkPdu();
    ~V2GetBulkPdu();
    V2GetBulkPdu(const V2GetBulkPdu& right);

    int      NonRepeaters();
    void     NonRepeaters(int value);

    int      MaxRepetitions();
    void     MaxRepetitions(int value);

};
#endif
