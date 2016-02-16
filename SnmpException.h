#define __SNMPEXCEPTION_H__


enum SnmpExceptionCode
{
  FIRSTSNMPEXCEPTION = 0,
  TESTMESSAGE,
  NULLMESSAGE,
  ILLEGALSETTOPDUTYPE,
  MAXSNMPEXCEPTION
};

static const char* mMessages[] = 
{
  "",

  // parsing errors
  "Test",
  
  // build errors
  "",
  
  // component errors
  "Illegal attempt to set PDU type"
};


class SnmpException
{

  private:

    int     mCode;

  protected:



  public:

    SnmpException(int code);
    ~SnmpException();

    const char* Reason();

};
#endif
