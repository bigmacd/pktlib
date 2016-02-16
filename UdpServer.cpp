
#ifndef __UDPSERVER_H__
#include "UdpServer.h"
#endif

#ifdef _USE_PACKETLIB
#include "vbs.h"
#endif

UdpServer::UdpServer(int port, unsigned int timeout)
          :Udp(port, timeout)
{
  mSaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (ErrorCode() != 0) return;
  if (bind(mSocket, (sockaddr*)&mSaddr, sizeof(mSaddr)))
    GetErrorCode();
  else
    mIsReady = TRUE;
}

UdpServer::UdpServer(int port, const char* interfaceIp)
          :Udp(port, 5)
{
  if (interfaceIp == NULL)
    mSaddr.sin_addr.s_addr = INADDR_ANY;
  else 
 mSaddr.sin_addr.s_addr = inet_addr(interfaceIp);//, &mSaddr.sin_addr);
  
  if (ErrorCode() != 0) return;
  if (bind(mSocket, (sockaddr*)&mSaddr, sizeof(mSaddr)))
    GetErrorCode();
  else
    mIsReady = TRUE;

}

UdpServer::~UdpServer()
{

}

int                  
UdpServer::Send(const char* buffer, 
		unsigned int length)
{
  if (mIsReady)
    return Udp::Send(buffer,
		     length,
		     (struct sockaddr*)&mLaddr,
		     sizeof(mLaddr));
  else
    return 0;
}
    
#ifdef _USE_PACKETLIB
int                  
UdpServer::Send(Packet* p)
{
  if (mIsReady)
    return Udp::Send(p,
		     (struct sockaddr*)&mLaddr,
		     sizeof(mLaddr));
  else
    return 0;
}

Packet*
UdpServer::Receive(int)
{
  if (mIsReady)
  {
    int len = sizeof(mLaddr);
    return Udp::Receive(0, 
			(struct sockaddr*)&mLaddr,
			&len);
  }
  else
    return NULL;
}
#endif

const char*          
UdpServer::Receive()
{
  if (mIsReady)
  {
    int lLen = sizeof(mLaddr);
    return Udp::Receive((struct sockaddr*)&mLaddr,
			&lLen);
  }
  else
    return NULL;
}

