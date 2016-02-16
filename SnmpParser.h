

#ifndef __SNMPPARSER_H__
#define __SNMPPARSER_H__

#ifdef _WIN32

#ifdef _WINDOWS
#include <windows.h>
#else
#include <afxwin.h>
#endif

#else
#ifndef __COMPAT_H__
#include "compat.h"
#endif
#endif

class Packet;

class SnmpParser
{

  private:

    bool         mIown;
    Packet*      mPacket;
    unsigned int mIndex;

    void         decodeLength(unsigned char* pduField, long* value);
    void         encodeLength(unsigned char* pduField, long* value);

    void         decodeTag(unsigned char* pduField, long* value);
    void         encodeTag(unsigned char* pduField, long* value);

    char         mErrorMessage[256];

  protected:



  public:

    SnmpParser(unsigned char* pdu, unsigned int length);
    ~SnmpParser();

    Packet*  packet();

    char*    getLastError() { return mErrorMessage; } 

};
#endif
