 

#ifndef __VARBIND_H__
#define __VARBIND_H__

#include "Build.h"
#include "compat.h"

unsigned int  ComputeIntValue(unsigned char* &pduPart, 
			      unsigned int size);
unsigned long ComputeLongValue(unsigned char* &pduPart, 
			       unsigned int size);
__int64 Compute64Value(unsigned char* &pduPart, 
			       unsigned int size);

unsigned int  calculateLengthLength(unsigned int len);
unsigned int  calculateTotalLengthLength(unsigned int len);


extern void  decodeLength(unsigned char* &pduField, 
			  long* value);
extern void  encodeLength(unsigned char* &pduField, 
			  long value);

extern void  decodeTag(unsigned char* &pduField, 
		       long* value);
extern void  encodeTag(unsigned char* &pduField, 
		       long value);

extern void  decodeOID(unsigned char* &pduField, 
		       long* value);
extern void  encodeOID(unsigned char* newvalue, 
		       int pduField, 
		       unsigned int& encodedLength);

extern void  decodeFirstSubId(unsigned char* &dataStart,
			      unsigned short* First,		       
			      unsigned short* Second);
extern void  encodeFirstSubId(unsigned char* &pduField,
			      int First,		       
			      int Second);

class Varbind : public Builder
{
  private:

    unsigned short  mLength;
    unsigned short  mType;
    const    char*  mTypeString;

  protected:

    char*           mPrintable;

  public:
    
    Varbind(unsigned short type, const char* typeString);
    Varbind(unsigned char* &pduPart, 
	    unsigned short type, 
	    const char* typeString);
    Varbind();
    virtual ~Varbind();

    
    unsigned short     Type()                       { return mType; } 
    // type is only set in constructor

    unsigned short     DataLength()                 { return mLength; }
    void               DataLength(unsigned short length){ mLength = length; }

    unsigned int       Length();

    virtual unsigned char*   Data() = 0;

    virtual const char* Printable() = 0;

    const char*         TypeString()                 { return mTypeString; }
    virtual void        Build(unsigned char*& pdu) = 0;
    
    Varbind*        Next;

};
#endif

