

#ifndef __PDU_H__
#define __PDU_H__

#include "Build.h"

#ifdef _WIN32

#ifdef _WINDOWS
#include <windows.h>
#else
#include <afxwin.h>
#endif

#endif

class Pdu : public Builder
{

  private:


  protected:


  public:

    Pdu(){};
    Pdu(const Pdu& right){};
    virtual ~Pdu(){};

    virtual int                RequestId()                 { return 0;    }
    virtual void               RequestId(int value)        {};

    virtual int                ErrorIndex()                { return 0;    }
    virtual void               ErrorIndex(int value)       {};

    virtual int                ErrorStatus()               { return 0;    }
    virtual void               ErrorStatus(int value)      {};

    virtual int                GenericTrapType()           { return 0;    }
    virtual void               GenericTrapType(int value)  {};

    virtual int                SpecificTrapType()          { return 0;    }
    virtual void               SpecificTrapType(int value) {};

    virtual unsigned long      TimeTicks()                 { return 0;    }
    virtual void               TimeTicks(unsigned long value)         {};

    virtual const char*        SenderIP()                  { return 0L; }
    virtual void               SenderIP(const char* value)            {};

    virtual const char*        SenderOID()                 { return 0L; }
    virtual void               SenderOID(const char* value)           {};


    // I (that is class Pdu) do not know how to do this!
    virtual unsigned int       Length() = 0;
    virtual void               Parse(unsigned char* &buffer) = 0;
    virtual void               Build(unsigned char*& pdu) = 0;
    virtual unsigned char      Type() = 0;

};

#endif

