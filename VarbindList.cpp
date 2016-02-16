

#ifndef __VARBINDLIST_H__
#include "VarbindList.h"
#endif

#ifndef __VARBIND_H__
#include "Varbind.h"
#endif

#ifndef __VBPAIR_H__
#include "VbPair.h"
#endif

#ifndef __SNMPTYPES_H__
#include "SnmpTypes.h"
#endif

#ifndef __COMPAT_H__
#include "compat.h"
#endif

VarbindList::VarbindList()
            :mHead(NULL)
{

}

VarbindList::VarbindList(const VarbindList& right)
{
	
}

VarbindList::VarbindList(VbPair* vbp)
            :mHead(vbp)
{
}

VarbindList::~VarbindList()
{
  while (mHead != NULL)
  {
    VbPair* temp = mHead->Next;
    delete mHead;
    mHead = temp;
  }
}

void
VarbindList::Build(unsigned char*& pdu)
{
  *pdu++ = SEQUENCE;
  encodeLength(pdu, Length() - (1 + calculateLengthLength(Length())));
  VbPair* tVbPair = mHead;
  while (tVbPair != NULL)
  {
    tVbPair->Build(pdu);
    tVbPair = tVbPair->Next;
  } // while (tVbPair != NULL)  
}

void
VarbindList::Add(VbPair* vb)
{
  if (mHead == NULL)
    mHead = vb;
  else
  {
    VbPair* t = mHead;
    while (t->Next != NULL)
      t = t->Next;
    t->Next = vb;
  }
}

VbPair*
VarbindList::FirstVbPair()
{
  return mHead;
}

VbPair*        
VarbindList::AddFirst(VbPair* vbp)
{
  VbPair* t = mHead;
  mHead = vbp;
  return t;
}

unsigned int
VarbindList::Length()
{
  unsigned int len = 1;  // the SEQUENCE octet

  VbPair* temp = mHead;
  while(temp != NULL)
  {
    //    len++; // the SEQUECE octet
    len += temp->Length();
    temp = temp->Next;
  }

  len += calculateTotalLengthLength(len);
  return len;
}
