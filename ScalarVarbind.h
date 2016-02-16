#ifndef __SCALARVARBIND_H__
#define __SCALARVARBIND_H__

#ifndef __VARBIND_H__
#include "Varbind.h"
#endif

class ScalarVarbind : public Varbind
{

  private:


  protected:

    unsigned long        mValue;

  public:


    ScalarVarbind(unsigned short type, const char* typeString);
    ScalarVarbind(unsigned char* &pduPart, 
		  unsigned short type, 
		  const char* typeString);
    ScalarVarbind();
    virtual ~ScalarVarbind(){};


    virtual void             Value(unsigned long value);
    virtual unsigned long    Value() { return mValue; }

    virtual unsigned char*   Data();
    virtual const char*      Printable();
    virtual void             Build(unsigned char*& pdu);
      
  

};
#endif
