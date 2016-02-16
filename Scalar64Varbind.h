#ifndef __SCALAR64VARBIND_H__
#define __SCALAR64VARBIND_H__

#ifndef __SCALARVARBIND_H__
#include "Varbind.h"
#endif

#ifndef __COMPAT_H__
#include "compat.h"
#endif

class Scalar64Varbind : public Varbind
{

  private:


  protected:

    __int64        mValue;

  public:


    Scalar64Varbind(unsigned short type, const char* typeString);
    Scalar64Varbind(unsigned char* &pduPart, 
		    unsigned short type, 
		    const char* typeString);
    Scalar64Varbind();
    virtual ~Scalar64Varbind(){};


    virtual void             Value(__int64 value);
    virtual __int64          Value() { return mValue; }

    virtual unsigned char*   Data();
    virtual const char*      Printable();
    virtual void             Build(unsigned char*& pdu);
      

};
#endif
