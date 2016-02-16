

#ifndef __VBPAIR_H__
#include "VbPair.h"
#endif

VbPair::VbPair()
       :mOidVarbind(0L),
	mVarbind(0L),
	Next(0L)
{

}

VbPair::VbPair(OidVarbind* oidvb, Varbind* vb)
       :mOidVarbind(oidvb),
	mVarbind(vb),
	Next(0L)
{

}

VbPair::~VbPair()
{
  if (mOidVarbind)
    delete mOidVarbind;
  if (mVarbind)
    delete mVarbind;
}

void          
VbPair::OIDVarbind(OidVarbind* oidvb)
{ 
  mOidVarbind = oidvb; 
}

void          
VbPair::VarBind(Varbind* vb)
{ 
  mVarbind = vb; 
}

VbPair::VbPair(const VbPair& right)
{
	
}

OidVarbind*   
VbPair::OIDVarbind()
{
  return mOidVarbind;
}

Varbind*      
VbPair::VarBind()
{
  return mVarbind;
}

void
VbPair::Build(unsigned char*& pdu)
{
  *pdu++ = SEQUENCE;
  encodeLength(pdu, Length() - (1 + calculateLengthLength(Length())));
  if (mOidVarbind != 0L)
    mOidVarbind->Build(pdu);
  if (mVarbind != 0L)
    mVarbind->Build(pdu);
  else
  {
    *pdu++ = NULLTAG;
    *pdu++ = 0;
  }
}

unsigned int  
VbPair::Length()
{
  unsigned int len = 1;  // the SEQUENCE octet

  if (mOidVarbind != 0L)
    len += mOidVarbind->Length();
  if (mVarbind != 0L)
    len += mVarbind->Length();
  else
    len += 2; // for NULLTAG and zero

  len += calculateLengthLength(len);
  return len;
}

