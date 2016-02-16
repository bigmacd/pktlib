
#ifndef __UDPSERVER_H__
#define __UDPSERVER_H__

#include "Udp.h"

class UdpServer : public Udp
{

 private:


 protected:


 public:

  UdpServer(int port, unsigned int timeout = 5);
  UdpServer(int port, const char* interfaceIp);
  ~UdpServer();

  int                  Send(const char* buffer, 
			    unsigned int length);
    
  int                  Send(Packet* p);
  Packet*              Receive(int);

  const char*          Receive();
};


#endif












