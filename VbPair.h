

#ifndef __VBPAIR_H__
#define __VBPAIR_H__


#ifndef __OIDVARBIND_H__
#include "OidVarbind.h"
#endif

#ifndef __VARBIND_H__
#include "Varbind.h"
#endif

#include "Build.h"


class VbPair : public Builder
{

  private:

    OidVarbind*   mOidVarbind;
    Varbind*      mVarbind;


  protected:



  public:

    VbPair();
    VbPair(OidVarbind* oidvb, Varbind* vb);
    VbPair(const VbPair& right);
    ~VbPair();

    VbPair*       Next;

    unsigned int  Length();

    OidVarbind*   OIDVarbind();
    void          OIDVarbind(OidVarbind* oidvb);

    Varbind*      VarBind();
    void          VarBind(Varbind* vb);

    virtual void  Build(unsigned char*& pdu);
};
#endif
