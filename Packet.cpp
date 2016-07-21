

#include "vbTypes.h"

#ifndef __PKTLIBVERSION_H__
#include "PktLibVersion.h"
#endif


Packet::Packet()
       :mCommunityVb(NULL),
        mVersionVb(NULL),
        mPdu(NULL),
        mVbList(NULL),
	mType(0),
	Next(NULL)
{
  mVbList = new VarbindList();
  mCommunityVb = new StringVarbind((char*)"public");  
}

Packet::Packet(unsigned int type, unsigned int version)
       :mCommunityVb(NULL),
        mVersionVb(NULL),
        mPdu(NULL),
        mVbList(NULL),
	mType(type),
	Next(NULL)
{
  mVbList = new VarbindList();
  mCommunityVb = new StringVarbind((char*)"public");

  if (type == INFORMPDU || type == GETBULK)
    version = 1;

  mVersionVb = new IntVarbind(version);
  Type(type);
}

Packet::Packet(const Packet& right)
{

}

Packet::~Packet()
{
  if (mVbList)
    delete mVbList;
  if (mCommunityVb)
    delete mCommunityVb;
  if (mVersionVb)
    delete mVersionVb;
  if (mPdu)
    delete mPdu;
}

const char* 
Packet::PktLibVersion()
{
  return gVersionNumber;
}

void
Packet::Type(unsigned int type)
{
  mType = type;
  switch (type)
  {
    case V1TRAP:
    {
      mPdu = new V1TrapPdu();
      break;
    }
    case V2TRAP:
    {
      mPdu = new V2TrapPdu();
      break;
    }
    case V1GETCOMMAND:
    {
      mPdu = new V1GetPdu();
      break;
    }
    case V1SETCOMMAND:
    {
      mPdu = new V1SetPdu();
      break;
    }
    case V1GETNEXTCOMMAND:
    {
      mPdu = new V1GetNextPdu();
      break;
    }
    case V1RESPONSE:
    {
      mPdu = new V1ResponsePdu();
      break;
    }
    case INFORMPDU:
    {
      mPdu = new InformPdu();
      break;
    }
    case GETBULK:
    {
      mPdu = new V2GetBulkPdu();
      break;
    }
  }
}

void
Packet::Add(VbPair* vbpair)
{
  if (mVbList != NULL)
    mVbList->Add(vbpair);
}

void
Packet::Build(unsigned char*& pdu)
{
  unsigned char* inpdu = pdu;
  *inpdu++ = SEQUENCE;
  encodeLength(inpdu, Length());
  if (mVersionVb)
    mVersionVb->Build(inpdu);
  if (mCommunityVb)
    mCommunityVb->Build(inpdu);

  if (mPdu)
  { 
    *inpdu++ = mPdu->Type();
    if (mVbList)
      encodeLength(inpdu, mPdu->Length() + mVbList->Length());
    else
      encodeLength(inpdu, mPdu->Length());

    mPdu->Build(inpdu);
    if (mVbList)
      mVbList->Build(inpdu);
  } 
}

void           
Packet::Version(IntVarbind* intvb) 
{ 
  if (mVersionVb)
    delete mVersionVb;
  mVersionVb = intvb; 
}


int
Packet::Version()
{
  if (mVersionVb)
    return mVersionVb->Value();
  throw(0);
  return 0;
}
 
void           
Packet::Version(int version)
{
  if (mVersionVb)
    delete mVersionVb;
  mVersionVb = new IntVarbind(version);
}


const char*    
Packet::Community()
{
  if (mCommunityVb)
    return mCommunityVb->Value();
  return NULL;
}

void           
Packet::Community(const char* community)
{
  if (mCommunityVb)
    delete mCommunityVb;
  mCommunityVb = new StringVarbind((char*)community);
}

void           
Packet::Community(StringVarbind* community)
{
  if (mCommunityVb)
    delete mCommunityVb;
  mCommunityVb = community; 
}

VarbindList*   
Packet::VbList()
{
  return mVbList;
}
 
void           
Packet::VbList(VarbindList* vblist)
{
  if (mVbList)
    delete mVbList;
  mVbList = vblist;
}

Pdu*           
Packet::pdu()
{
  return mPdu;
}

void           
Packet::pdu(Pdu* inPdu)
{
  if (mPdu)
    delete mPdu;
  mPdu = inPdu;
}

unsigned int     
Packet::TotalLength()
{
  unsigned int len = Length();
  len += calculateTotalLengthLength(len);
  return ++len; // the SEQUENCE
}

unsigned int     
Packet::Length()
{
  unsigned int len = 0;
  unsigned int pduLen = 0;
  unsigned int vbLen = 0;

  if (mVersionVb != NULL)
    len += mVersionVb->Length();

  if (mCommunityVb != NULL)
    len += mCommunityVb->Length();
  
  len++;  // for the type octet

  if (mPdu)
    pduLen = mPdu->Length();
  len += pduLen;

  if (mVbList != NULL)
    vbLen = mVbList->Length();

  len += vbLen;


  // how many octets for length?
  len += calculateTotalLengthLength(pduLen + vbLen);

  return len;
}

// from the pdu interface
int                
Packet::RequestId()
{
  if (mPdu)
    return mPdu->RequestId();
  return 0;
}

void               
Packet::RequestId(int value)
{
  if (mPdu)
    mPdu->RequestId(value);
}

int                
Packet::ErrorIndex()
{
  if (mPdu)
    return mPdu->ErrorIndex();
  return 0;
}

void               
Packet::ErrorIndex(int value)
{
  if (mPdu)
    mPdu->ErrorIndex(value);
}

int                
Packet::ErrorStatus()
{
  if (mPdu)
    return mPdu->ErrorStatus();
  return 0;
}

void               
Packet::ErrorStatus(int value)
{
  if (mPdu)
    mPdu->ErrorStatus(value);
}

int                
Packet::GenericTrapType()
{
  if (mPdu)
  {
    if (mPdu->Type() == V2TRAP || mPdu->Type() == INFORMPDU)
      return ENTERPRISESPECIFIC;
    else
      return mPdu->GenericTrapType();
  }
  return 0;
}

void               
Packet::GenericTrapType(int value)
{
  if (mPdu)
    mPdu->GenericTrapType(value);
}

int                
Packet::SpecificTrapType()
{
  if (mPdu)
  {
    if (mPdu->Type() == V2TRAP || mPdu->Type() == INFORMPDU)
    {
      const char* vbd = VbData(2);
      if (vbd != NULL)
      {
#ifdef _BORLAND
	const char* c = strrchr(vbd, '.');
#else
	const char* c = strrchr(vbd, '.');
#endif
	if (c != NULL)
	  return (atoi(++c));
      }
    }
    else
      return mPdu->SpecificTrapType();
  }
  return 0;
}

void               
Packet::SpecificTrapType(int value)
{
  if (mPdu)
    mPdu->SpecificTrapType(value);
}

unsigned long      
Packet::TimeTicks()
{
  if (mPdu)
    return mPdu->TimeTicks();
  return 0;
}

void               
Packet::TimeTicks(unsigned long value)
{
  if (mPdu)
    mPdu->TimeTicks(value);
}

const char*        
Packet::SenderIP()
{
  if (mPdu)
    return mPdu->SenderIP();
  return NULL;
}

void               
Packet::SenderIP(const char* value)
{
  if (mPdu)
    mPdu->SenderIP(value);
}

const char*
Packet::RealIp()
{
  struct in_addr a;
  a.s_addr = mRealIp;
  return inet_ntoa(a);
}

void
Packet::RealIp(struct sockaddr_in* peer)
{
  mRealIp = peer->sin_addr.s_addr;
}

const char*        
Packet::SenderOID()
{
  if (mPdu)
  {
    if (mPdu->Type() == INFORMPDU || mPdu->Type() == V2TRAP)
    {
      if (VbListLength() >= 2)
      {
	const char* vbtype = VbType(2);
	if (vbtype)
	  if (!strcmp(vbtype, "OID"))
	    return VbData(2);
      }
    }
    else
      return mPdu->SenderOID();
  }
  return NULL;
}

void               
Packet::SenderOID(const char* value)
{
  if (mPdu)
    mPdu->SenderOID(value);
}

unsigned char
Packet::Type()
{
  if (mPdu)
    return mPdu->Type();
  return 0xff;
}

int            
Packet::VbListLength()
{
  int vbCount = 0;
  VbPair* vb = mVbList->FirstVbPair();
  while (vb != NULL)
  {
    vbCount++;
    vb = vb->Next;
  }
  return vbCount;
}

const char*    
Packet::VbOID(int which)
{
  VbPair* vbp = GetVbNumber(which);
  if (vbp != NULL)
  {
    OidVarbind* ovb = vbp->OIDVarbind();
    return ovb->Printable();
  }
  else
    return "NULL";
}

const char*    
Packet::VbType(int which)
{
  VbPair* vbp = GetVbNumber(which);
  if (vbp != NULL)
  {
    Varbind* vb = vbp->VarBind();
    return vb->TypeString();
  }
  else
    return "NULL";
}

const char*    
Packet::VbData(int which)
{
  VbPair* vbp = GetVbNumber(which);
  if (vbp != NULL)
  {
    Varbind* vb = vbp->VarBind();
    return vb->Printable();
  }
  else
    return "NULL";
}

VbPair*
Packet::GetVbNumber(int which)
{
  VbPair* vb = mVbList->FirstVbPair();
  which--;
  while (which-- && vb)
    vb = vb->Next;

  return vb;
}

void
Packet::AddV2TrapVarbinds(unsigned long counterValue,
			  char* trapOidValue,
			  int genericType,
			  int specificType,
			  bool noSubIds)
{
  if (mType == V2TRAP || mType == INFORMPDU)
  {
    if (mVbList != NULL)
    {
      OidVarbind* timestampOid = new OidVarbind((char*)"1.3.6.1.2.1.1.3.0");
      TimetickVarbind* ttVb = new TimetickVarbind(counterValue);      
      VbPair* vbp1 = new VbPair(timestampOid, ttVb);
      
      OidVarbind* trapOidOid = new OidVarbind((char*)"1.3.6.1.6.3.1.1.4.1.0");

      char* value = NULL;
      if (genericType < 6 && genericType >= 0)
      {
	value = new char [20];
#ifdef _WIN32
	sprintf_s(value, 20, "%s%d", "1.3.6.1.6.3.1.1.5.", genericType + 1);
#else
	sprintf(value, "%s%d", "1.3.6.1.6.3.1.1.5.", genericType + 1);
#endif
      }
      else
      {
	value = new char [strlen(trapOidValue) + 103];
	if (noSubIds) 
	{
#ifdef _WIN32
	  sprintf_s(value, strlen(trapOidValue) + 103, "%s", trapOidValue);
#else
	  sprintf(value, "%s", trapOidValue);
#endif  
	}
	else // the default
	{
#ifdef _WIN32
	  sprintf_s(value, strlen(trapOidValue) + 103, "%s.0.%d", trapOidValue, specificType);
#else
	  sprintf(value, "%s.0.%d", trapOidValue, specificType);
#endif  
	}
      }
      OidVarbind* trapOid = new OidVarbind(value);

      VbPair* vbp2 = new VbPair(trapOidOid, trapOid);
      
      VbPair* saveVbp = mVbList->AddFirst(vbp1);
      mVbList->Add(vbp2);
      mVbList->Add(saveVbp);

      delete [] value;
    }
  }
}
    
