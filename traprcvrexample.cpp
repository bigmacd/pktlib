// This source code demonstrates the trap receiption ability of 
// Network Computing  Technologies' SNMP packet library (pktlib). 

#ifdef _WIN32
#include <winsock.h>
#endif

#include <stdio.h>  
#include <stdlib.h>
#include <iostream.h>
#include <ctype.h>
#include <memory.h>  
#include "Packet.h" 
#include "vbTypes.h" 
#include "SnmpTypes.h" 
#include "SnmpParser.h"  
#include "UdpClient.h"
#include "UdpServer.h"
#include <string.h>

void main(int argc, char** argv)  
{ 

#ifdef _WIN32
  // normal socket setup stuff 
  WSADATA wsaData; 
  int err = WSAStartup(0x101, &wsaData); 
  if (err == WSAVERNOTSUPPORTED) 
    err = WSAStartup(0x101, &wsaData); 
#endif  

  UdpServer udpS(162);  // Open the UdpServer on port 162, listening
  // Suggest: UdpServer udpS(162, 0); Sets timeout to zero, thereby 
  // blocking on socket until something comes in

  for (;;)  // Loop forever
  {

    Packet* p = udpS.Receive(0);
    if(p != NULL)
    {
      int type = p->Type();
      if (type == V1TRAP || type == V2TRAP || type == INFORMPDU)
      {
	int numOfVarBinds = p->VbListLength(); // Get the number of Variables
	  
	cout << "Received Trap." << endl;
	cout << "Version is             : " << p->Version() << endl;
	cout << "Community is           : " << p->Community() << endl;
	cout << "Generic Type is        : " << p->GenericTrapType() << endl;
	cout << "Specific Type is       : " << p->SpecificTrapType() << endl;
	cout << "TimeStamp is           : " << p->TimeTicks() << endl;
	cout << "Sender's IP Address is : " << p->SenderIP() << endl;
	cout << "Sender's OID is        : " << p->SenderOID() << endl;

	cout << "Trap contained " << numOfVarBinds << " varbinds." << endl;

	for (int counter = 1; counter <= numOfVarBinds; counter++)
	{
	  cout << "Varbind " << counter << endl;
	  cout << "\tOID is " << p->VbOID(counter) << endl;
	  cout << "\tType is " << p->VbType(counter) << endl;
	  cout << "\tData is " << p->VbData(counter) << endl;
	}

	if (type == INFORMPDU)
	{
	  V1Pdu* pdu = (V1Pdu*)(p->pdu());
	  if (pdu != NULL)
	  {
	    pdu->MakeResponsePdu(); // turns it into an INFORM response
	    p->ErrorIndex(0);
	    p->ErrorStatus(NOERROR);
	    udp.Send(p); // sends the INFORM response back
	  } // if (pdu != NULL)
	} // if (type == INFORMPDU)

      } // if (p->Type() == V1TRAP ...)
      delete p;
    } // if (p != NULL)
  } // for (;;)
}


