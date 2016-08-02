#ifndef __UDP_H__
#include "Udp.h"
#endif

#ifdef _USE_PACKETLIB
#include "vbs.h"
#endif

Udp::Udp()
    :mReadBuffer(NULL),
     mReadLength(0),
     mSocket(INVALID_SOCKET),
     mIsReady(FALSE),
     mErrorCode(0),
     mTimeout(5)
{
  CommonInit();
}

Udp::Udp(int port, unsigned int timeout)
    :mReadBuffer(NULL),
     mPort(port),
     mTimeout(timeout),
     mReadLength(0),
     mSocket(INVALID_SOCKET),
     mIsReady(FALSE),
     mErrorCode(0)
{
  CommonInit();
  Port(mPort);
}

Udp::~Udp()
{
  if (mReadBuffer != NULL)
    delete [] mReadBuffer;

  if (mSocket != INVALID_SOCKET)
  {
#ifdef _WIN32
    closesocket(mSocket);
#else
    close(mSocket);
#endif
  }
}

void
Udp::CommonInit()
{
  memset(&mSaddr, 0, sizeof(mSaddr)); 
  memset(&mLaddr, 0, sizeof(mLaddr)); 
  ReadBufferSize(4096);  // the default

#ifdef _WIN32
  mSocket = socket(AF_INET, SOCK_DGRAM, 0);
#else
  mSocket = socket(AF_INET, SOCK_DGRAM, 0);
#endif
  if (mSocket == INVALID_SOCKET) 
    GetErrorCode();
  mSaddr.sin_family = AF_INET;

  // 
  int opt = 1;
  setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(int));
  //
}

void
Udp::Port(int port)
{
  mPort = port;
  mSaddr.sin_port = htons(mPort);
}


int
Udp::Send(const char* buffer, 
	  unsigned int length,
	  struct sockaddr* s,
	  int sLen)
{
  int sendLen = 0;

  sendLen = sendto(mSocket, 
		   buffer, 
		   length, 
		   0, 
		   s,
		   sLen);
  if (sendLen < 0)
  {
    GetErrorCode();
    sendLen = 0;
  }

  return sendLen;
}

const char*
Udp::Receive(struct sockaddr* s, int* sLen)
{
  char* retVal = NULL;
  char* tempBuffer = new char[mReadBufferSize];
  mReadLength = 0;

#ifndef _LINUX
  struct fd_set fds;
#else
  fd_set fds;
#endif

#ifdef _HPUX
  struct sockaddr ss;
  s = &ss;
  int ssLen;
  sLen = &ssLen;
#endif

  FD_ZERO(&fds);
  FD_SET(mSocket, &fds);
  
  struct timeval tv;
  tv.tv_sec = mTimeout;
  tv.tv_usec = 0;
  struct timeval* tvp;
  if (mTimeout == 0)
    tvp = NULL;
  else
    tvp = &tv;

#ifdef _WIN32
  int ReadyCount = select(0, &fds, NULL, NULL, tvp);
#else
  int ReadyCount = select(mSocket + 1, &fds, NULL, NULL, tvp);
#endif
  
  if (ReadyCount > 0)
  {
    mReadLength = recvfrom(mSocket,
			   tempBuffer, 
			   mReadBufferSize, 
			   0, 
			   s,
#if defined(_LINUX) || defined(_FREEBSD) || defined(_SOLARIS)
			   (socklen_t*)sLen);
#else
			   sLen);
#endif
    if (mReadLength > 0)
    {
      memset(mReadBuffer, 0, mReadBufferSize);
      memcpy(mReadBuffer, tempBuffer, mReadLength);
    }
    else
    {
      GetErrorCode();
      mReadLength = 0;
    }
    
    if (mReadLength > 0)
      retVal = mReadBuffer;
  }
  delete [] tempBuffer;
    
  return retVal;
}

void
Udp::ReadBufferSize(unsigned int size)
{
  if (mReadBuffer != NULL)
    delete [] mReadBuffer;
  mReadBufferSize = size;
  mReadBuffer = new char[mReadBufferSize];
}

void
Udp::GetErrorCode()
{
#ifdef _WIN32
  mErrorCode = WSAGetLastError();
#else
  mErrorCode = errno;
#endif
}

#ifdef _USE_PACKETLIB
int
Udp::Send(Packet* p, struct sockaddr* s, int sLen)
{
  int retVal = 0;
  
  try 
  {
    unsigned long len = p->TotalLength();    
    unsigned char* t = new unsigned char[len + 100];
    memset(t, 0, len + 100);
    p->Build(t);

#ifdef _DEBUG
//for (unsigned long x = 0; x < len; x++)
// {
//   if (x && !(x % 10)) printf("\r\n");
//   printf("%02x ", t[x]);
// }
#endif

    retVal = Send((const char*)t, len, s, sLen);
    delete [] t;
  }
  catch(...)
  {
    retVal = 0;
  }
  
  return retVal;
}

Packet*
Udp::Receive(int, struct sockaddr* s, int* sLen)
{
  Packet* pkt = NULL;
  const char* buf = Receive(s, sLen);
  unsigned int len = mReadLength;
  mWasParserError = false;

  if (len > 0)
  {
    memset(mParserErrorMessage, 0, 256);

    SnmpParser p((unsigned char*)buf, len);
    pkt = p.packet();

    if (NULL == pkt) {
      mWasParserError = true;
      strncpy(mParserErrorMessage, p.getLastError(), 255);
    }
  }

  return pkt;
}
#endif

