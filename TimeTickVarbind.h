

#ifndef __TIMETICKVARBIND_H__
#define __TIMETICKVARBIND_H__

#ifndef __SCALARVARBIND_H__
#include "ScalarVarbind.h"
#endif

#include "SnmpTypes.h"

class TimetickVarbind : public ScalarVarbind
{
  private:


  protected:



  public:
    
    TimetickVarbind();
    TimetickVarbind(unsigned char* &pduPart);
    TimetickVarbind(unsigned long timetick);
    ~TimetickVarbind();

    virtual void           Build(unsigned char*& pdu);
   
};
#endif
