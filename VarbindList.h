

#ifndef __VARBINDLIST_H__
#define __VARBINDLIST_H__

#include "Build.h"

class VbPair;

class VarbindList : public Builder
{
  private:

    VbPair*       mHead;

  protected:



  public:

    VarbindList();
    VarbindList(VbPair* vbp);
    ~VarbindList();	  
    
    VarbindList(const VarbindList& right);

    unsigned int  Length();

    void           Add(VbPair* vbp);
    VbPair*        AddFirst(VbPair* vbp);

    VbPair*        FirstVbPair();

    virtual void   Build(unsigned char*& pdu);
};
#endif
