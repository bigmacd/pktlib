
#ifndef __UDPV6_H__
#define __UDPV6_H__

#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#ifdef _WINDOWS
#include <winsock2.h>
#else
#include <afxsock.h>
#endif
#endif

#ifndef __COMPAT_H__
#include "compat.h"
#endif

class Packet;

class UdpV6
{

 private:

  int                     mPort;
  unsigned int            mReadBufferSize;
  char*                   mReadBuffer;
  int                     mReadLength;
  long                    mErrorCode;
  unsigned int            mTimeout;
  void                    CommonInit();
 

 protected:

  SOCKET                  mSocket;  
  struct sockaddr_in      mSaddr;
  struct sockaddr_in      mLaddr;
  bool                    mIsReady;
  void                    GetErrorCode();
  int                     Send(const char* buffer, 
			       unsigned int length,
			       struct sockaddr* s,
			       int sLen);

  int                     Send(Packet* p,
			       struct sockaddr* s,
			       int sLen);
  Packet*                 Receive(int, struct sockaddr* s, int* sLen);

  const char*             Receive(struct sockaddr* s, int* sLen);
  char                    mParserErrorMessage[256];
  bool                    mWasParserError;

 public:

  UdpV6();
  UdpV6(int port, unsigned int timeout = 5);
  ~UdpV6();

  void         ReadBufferSize(unsigned int size);
  unsigned int ReadBufferSize() { return mReadBufferSize; }

  void         Port(int port);
  int          Port()  { return mPort; }

  SOCKET       Socket() { return mSocket; }

  bool         IsReady()  { return mIsReady; }

  int          ReadLength() { return mReadLength; }

  long         ErrorCode()  { return mErrorCode; }

  unsigned int Timeout() { return mTimeout; }
  void         Timeout(unsigned int timeout) { mTimeout = timeout; }

  struct sockaddr_in* Peer() { return &mLaddr; }  

  char*        ParserErrorMessage() { return mParserErrorMessage; }
  bool         WasParserError() { return mWasParserError; }

};

#endif


























