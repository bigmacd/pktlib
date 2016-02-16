#include "Security.h"
#endif


Security::Security()
{
  mSecurityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
  mSecurityAttributes.bInheritHandle = TRUE;

  // setting this security descriptor properly can effect 
  // (not affect) chroot
  InitializeSecurityDescriptor(&mSecurityDescriptor,
			       SECURITY_DESCRIPTOR_REVISION);
  mSecurityAttributes.lpSecurityDescriptor = &mSecurityDescriptor;
}

Security::~Security()
{

}

SECURITY_ATTRIBUTES  
Security::SecurityAttributes() const
{ 
  return mSecurityAttributes; 
}

void                 
Security::SecurityAttributes(SECURITY_ATTRIBUTES sa)
{ 
  mSecurityAttributes = sa; 
}

