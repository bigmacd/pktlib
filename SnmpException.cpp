#include "SnmpException.h"
#endif


SnmpException::SnmpException(int code)
              :mCode(code)
{
  if (mCode < FIRSTSNMPEXCEPTION || 
      mCode >= MAXSNMPEXCEPTION)
    mCode = 0;
  throw(this);
}

SnmpException::~SnmpException()
{

}

const char* 
SnmpException::Reason()
{
  return (const char*)mMessages[mCode];
}
