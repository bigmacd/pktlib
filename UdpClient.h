
#ifndef __UDPCLIENT_H__
#define __UDPCLIENT_H__

#include "Udp.h"

class UdpClient : public Udp
{

 private:

  char*                mHost;
  void                 CommonInit();

 protected:


 public:

  UdpClient();
  UdpClient(int port, char* host);
  ~UdpClient();

  char*                Host() { return mHost; }
  void                 Host(char* host);

  int                  Send(const char* buffer, 
			    unsigned int length);
    
  int                  Send(Packet* p);
  Packet*              Receive(int);

  const char*          Receive();
};

#endif
