

#ifndef __V2NOTIFICATION_H__
#define __V2NOTIFICATION_H__

#ifndef __V1PDU_H__
#include "V1Pdu.h"
#endif

#ifndef _WIN32
#include <netinet/in.h>
#endif


class V2Notification : public V1Pdu
{
  private:

    long mPeerAddr;

  protected:


  public:

    V2Notification();
    virtual ~V2Notification();

    virtual const char*        SenderIP();
    void                       SenderIP(struct sockaddr_in* peer);

};
#endif






