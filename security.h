#ifndef __SECURITY_H__
#define __SECURITY_H__

#ifdef _BORLAND
#include <windows.h>
#else
#ifdef CONSOLE
#include <windows.h>
#else
#include <afxwin.h>
#endif
#endif

class Security
{


  private:

    SECURITY_ATTRIBUTES   mSecurityAttributes;
    SECURITY_DESCRIPTOR   mSecurityDescriptor;


  protected:



  public:

    Security();    
    Security(const Security& right);    
    ~Security();

    SECURITY_ATTRIBUTES  SecurityAttributes() const;
    void                 SecurityAttributes(SECURITY_ATTRIBUTES sa);

    const SECURITY_DESCRIPTOR  SecurityDescriptor() 
                                   { return mSecurityDescriptor; }
    void                       SecurityDescriptor(SECURITY_DESCRIPTOR sd) 
                                   { mSecurityDescriptor = sd; }

    // expose the security object's properties
  
    //  The length 
    unsigned long SoLength();
    // void SoLength(unsigned long length);  set internally only
  
    //  The Inherit Handle Flag
    BOOL          InheritHandle();
    void          InheritHandle(BOOL flag);

    //  The Security Descriptor
    //  the SD is a void*.  Here are the contents.
    /*
    Revision;
    Sbz1;
    Control; 
    Owner;
    Group;
    Sacl;
    Sacl.AclRevision;
    Sacl.Sbz1;
    Sacl.AclSize;
    Sacl.AceCount;
    Sacl.Sbz2;
    Dacl;
    Dacl.AclRevision;
    Dacl.Sbz1;
    Dacl.AclSize;
    Dacl.AceCount;
    Dacl.Sbz2;  */

};
#endif


