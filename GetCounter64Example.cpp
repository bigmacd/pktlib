#include "UdpClient.h"
#include "SnmpTypes.h"
#include "vbs.h"

int main (int argc, char** argv)
{
  // Windows winsock startup - typical
  WSAData d;
  WSAStartup(0x101, &d);

  // one of these always come in handy
  UdpClient udp;
  udp.Port(161);
  udp.Host("216.177.47.44");

  // ok, I know.  The packet type for V1 and V2 is the same 
  // (V1GETCOMMAND) but to support 64 bit counters we need
  // to specify protocol version SNMPv2c or, um, '1'.
  Packet p(V1GETCOMMAND, 1);

  p.Community("public");

  // these oids are for ifHCInOctets
  // we will try to get the first seven instances
  char* baseOid = "1.3.6.1.2.1.31.1.1.1.6.%d";
  for (int x = 1; x <= 7; x++)
  {
    char temp[128];
    memset(temp, 0, 128);
    sprintf(temp, baseOid, x);
    OidVarbind* o = new OidVarbind(temp);
    VbPair* vbp = new VbPair(o, NULL);
    p.Add(vbp);
  }
  
  udp.Send(&p);

  Packet* retP = udp.Receive(0);
  if (retP != NULL) // ya never know, and if you think you do then
  {                 // put down that editor and back away slowly
    int len = retP->VbListLength();
    cout << "list len is " << len << endl;
    for (int x = 1; x <= len; x++)
    {
      cout << "vboid: " << retP->VbOID(x) << endl;
      cout << "vbtype: " << retP->VbType(x) << endl;
      cout << "vbdata: " << retP->VbData(x) << endl;
    }
    cout << endl;
  }
  else
    cout << "retP is null" << endl;


  WSACleanup();
  return 1;
}
