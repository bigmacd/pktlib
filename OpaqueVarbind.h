

#ifndef __OPAQUEVARBIND_H__
#define __OPAQUEVARBIND_H__

#ifndef __VARBIND_H__
#include "Varbind.h"
#endif

#include "SnmpTypes.h"

class OpaqueVarbind : public Varbind
{
  private:

    unsigned char*         mData;
  
  protected:



  public:
    
    OpaqueVarbind();
    OpaqueVarbind(unsigned char* &pduPart);
    OpaqueVarbind(unsigned char* value, unsigned int length);
    OpaqueVarbind(char* value, unsigned int length);
    OpaqueVarbind(char value);
    OpaqueVarbind(unsigned long value);
    OpaqueVarbind(long value);
    OpaqueVarbind(unsigned char value);
    OpaqueVarbind(unsigned int value);
    OpaqueVarbind(int value );
    OpaqueVarbind(unsigned short value);
    OpaqueVarbind(short value);
   ~OpaqueVarbind();

    void                   Value(unsigned long value);
    void                   Value(long value);  

    void                   Value(unsigned char* value, unsigned int length);
    void                   Value(unsigned char value);

    void                   Value(char* value, unsigned int length);
    void                   Value(char value);
  
    void                   Value(unsigned int value);
    void                   Value(int value);

    void                   Value(unsigned short value);
    void                   Value(short value);

    const char*            Value();

    virtual const char*    Printable();
    virtual unsigned char* Data();
    virtual void           Build(unsigned char*& pdu);

        
};
#endif
