
#ifndef __GENERICPACKET_H__
#define __GENERICPACKET_H__

#ifndef __BUILD_H__
#include "Build.h"
#endif

  //#ifdef _WINDOWS
  //#include <afxwin.h>
  //#else
  //#ifdef _WIN32
  //#include <windows.h>

  //#ifdef _AFXDLL
  //#  include "stdafx.h"
  //#else
  //#  if _WIN32
  //#    include "windows.h"
  //#endif
  //#endif

#include <time.h>

#ifndef __COMPAT_H__
  //#include "compat.h"
#endif

class GenericPacket : public Builder
{
  private:

    int            mSequenceNumber;
    time_t         mTimeStamp;
    unsigned long  mPeerAddress;

  protected:


  public:

    GenericPacket();
    virtual ~GenericPacket();

    time_t         TimeStamp() { return mTimeStamp; }
    void           TimeStamp(time_t t) { mTimeStamp = t; }

    unsigned long  PeerAddress() { return mPeerAddress; }
    void           PeerAddress(unsigned long peerAddress) 
    { mPeerAddress = peerAddress; }

    GenericPacket* Next;

    virtual unsigned int     TotalLength() = 0;
    virtual int              Version() = 0;
    virtual const char*      Community() = 0; 
    virtual int              VbListLength() = 0;
    virtual const char*      VbOID(int which) = 0;
    virtual const char*      VbType(int which) = 0;
    virtual const char*      VbData(int which) = 0;
    virtual int              RequestId() = 0;
    virtual int              ErrorIndex() = 0;
    virtual int              ErrorStatus() = 0;
    virtual int              GenericTrapType() = 0;
    virtual int              SpecificTrapType() = 0;
    virtual unsigned long    TimeTicks() = 0;
    virtual const char*      SenderIP() = 0;
    virtual const char*      SenderOID() = 0;
    virtual unsigned char    Type() = 0;
    virtual void             AddV2TrapVarbinds(unsigned long counterValue,
					       char* trapOidValue,
	                                       int genericType = 6,
	                                       int specificType = 1) {};
    
};

#endif










