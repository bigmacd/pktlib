
#ifndef __UDPCLIENT_H__
#include "UdpClient.h"
#endif

#ifdef _USE_PACKETLIB
#include "vbs.h"
#endif

UdpClient::UdpClient()
          :Udp(),
	   mHost(NULL)
{

}

UdpClient::UdpClient(int port, char* host)
          :Udp(port),
	   mHost(NULL)
{
  Host(host);
}

UdpClient::~UdpClient()
{
  if (mHost != NULL)
    delete [] mHost;
}

void
UdpClient::CommonInit()
{
  // figure out if it is name or decimal dot notation
  unsigned long addr = inet_addr(mHost);
  if (addr == INADDR_NONE)
  {
    HOSTENT* hp = gethostbyname(mHost);
    if (hp != NULL)
    {
      memcpy((char*)&(mSaddr.sin_addr.s_addr),
	     hp->h_addr,
	     hp->h_length);
    }
    else
    {
      GetErrorCode();
      return;
    }
  }
  else
    mSaddr.sin_addr.s_addr = addr;

  mLaddr.sin_family = AF_INET;
  mLaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  mLaddr.sin_port = htons(0);

  if (bind(mSocket, (sockaddr*)&mLaddr, sizeof(mLaddr)))
    GetErrorCode();
  else
    mIsReady = TRUE;
}

void
UdpClient::Host(char* host)
{
  if (strlen(host) > 0)
  {
    mHost = new char[strlen(host) + 1];
    memset(mHost, 0, strlen(host) + 1);
#ifdef _WIN32
    strcpy_s(mHost, strlen(host) + 1, host);
#else
    strcpy(mHost, host);
#endif
  }
  CommonInit();
}

int                  
UdpClient::Send(const char* buffer, 
		unsigned int length)
{
  if (mIsReady)
    return Udp::Send(buffer,
		     length,
		     (struct sockaddr*)&mSaddr,
		     sizeof(mSaddr));
  else
    return 0;
}
    
#ifdef _USE_PACKETLIB
int                  
UdpClient::Send(Packet* p)
{
  if (mIsReady)
    return Udp::Send(p, (struct sockaddr*)&mSaddr, sizeof(mSaddr));
  else
    return 0;
}

Packet*
UdpClient::Receive(int)
{
  if (mIsReady)
    return Udp::Receive(0, (struct sockaddr*)0, (int*)0);
  else
    return NULL;
}
#endif

const char*          
UdpClient::Receive()
{
  if (mIsReady)
    return Udp::Receive((struct sockaddr*)0, (int*)0);
  else
    return NULL;
}



