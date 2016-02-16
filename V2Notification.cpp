

#ifndef __V2NOTIFICATION_H__
#include "V2Notification.h"
#endif

#ifndef _WIN32
#include <arpa/inet.h>
#else
#include <winsock.h>
#endif


V2Notification::V2Notification()  
               :mPeerAddr(-1)
{

}

V2Notification::~V2Notification()
{

}

const char*        
V2Notification::SenderIP()
{
  struct in_addr a;
  a.s_addr = mPeerAddr;
  return inet_ntoa(a);
}

void                       
V2Notification::SenderIP(struct sockaddr_in* peer)
{
  mPeerAddr = peer->sin_addr.s_addr;
}







