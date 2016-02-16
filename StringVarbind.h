

#ifndef __STRINGVARBIND_H__
#define __STRINGVARBIND_H__

#ifndef __VARBIND_H__
#include "Varbind.h"
#endif

#include "SnmpTypes.h"

class StringVarbind : public Varbind
{
  private:

    bool           mHexData;
    unsigned char* mData;

  protected:



  public:
  
    StringVarbind();
    StringVarbind(unsigned char* &pduPart);
    StringVarbind(char* string);
    StringVarbind(char* string, int len);
    ~StringVarbind();
  
    void                   Value(char* string);
    const char*            Value();
    virtual const char*    Printable();
  
    virtual void           Build(unsigned char*& pdu);
    virtual unsigned char* Data();
};
#endif





