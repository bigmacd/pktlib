//  This source code demonstrates the technique by which one would
//  issue an SNMPv2c GetBulk command and process the response,

#include "vbs.h"
#include "UdpClient.h"
#include <iostream.h>

void OutputPacket(Packet* gPacket);

int main(int argc, char** argv)
{
    WSADATA			wsaData;
	Packet			p(GETBULK, 1);
	OidVarbind*		oid1;
	OidVarbind*		oid2;
	VbPair*			vbp1;
	VbPair*			vbp2;


	cout << "version is: " << p.PktLibVersion() << endl;
	
	int				len = 1;
	const char*		r=NULL;

	WSAStartup(0x101, &wsaData);
	printf("WSAStartup\n");

	p.Community("public");								// set the community string
	printf("Community set\n");

	p.ErrorStatus(1); // number of non-repeaters
	printf("Non-repeaters set to 1\n");

	p.ErrorIndex(5);  // number of max-repetitions
	printf("Repititions set to 5\n");

	oid1 = new OidVarbind("1.3.6.1.2.1.1"); // system
	vbp1 = new VbPair(oid1, NULL);
	p.Add(vbp1);
	printf("System OID set\n");

	oid2 = new OidVarbind("1.3.6.1.2.1.2.2"); // iftable
	vbp2 = new VbPair(oid2, NULL);
	p.Add(vbp2);
	printf("ifTable OID set\n");

	// that should be the easy part, that is getting the packet setup

	UdpClient udp(161, "192.168.1.33");
	printf("Packet set up to 192.168.1.33\n");
	OutputPacket(&p);

	int sendlen = udp.Send(&p);
	cout << "sent " << sendlen << " bytes" << endl;
	printf("Packet sent\n");

	// even that was pretty easy, that being getting the request out onto the wire

	// get the response!
	udp.Timeout(5);
	printf("Timeout set to 5 seconds\n");

	// for GetBulk, the size of the response is usually bigger than the default 4K bytes
	// kick it up here to support a bigger response
	// remember, the response is still a single UDP datagram (although on the wire it is multiple
	// packets, just fragmented).
	udp.ReadBufferSize(65535);
	printf("Read buffer set to 65535 bytes\n");

	r = udp.Receive();
	// note: if r is null, check the error code

	if (r == NULL)
	{
		printf("No packet received\n");
		long x = udp.ErrorCode();
		printf("Error: %u\n", x);
		return 0;
	}

	printf("Packet received\n");

	// an errorcode of 10040 (WSAEMSGSIZE) means your buffer (ReadBufferSize) wasn't big enough
	len = udp.ReadLength();

	cout << "read <" << len << "> bytes" << endl;

	SnmpParser parser((unsigned char*)r, len);
	Packet* gPacket = parser.packet();
	if (NULL != gPacket)
	{
	  OutputPacket(gPacket);
	} // if (NULL != gPacket)


	// second request
#if 0
	oid1 = new OidVarbind("1.3.6.1.2.1.1.2"); // system object id
	vbp1 = new VbPair(oid1, NULL);
	p.Add(vbp1);
	printf("System OID set\n");

	oid2 = new OidVarbind("1.3.6.1.2.1.2.2.1.2"); // ifDescr
	vbp2 = new VbPair(oid2, NULL);
	p.Add(vbp2);
	printf("ifTable OID set\n");
#endif
	/////////////////// start of second request
	{
	  VarbindList* oldVbl = p.VbList();
	  VbPair* oldVbp = oldVbl->FirstVbPair();

	  OidVarbind* oldOidVb1 = oldVbp->OIDVarbind();
	  oldOidVb1->Value("1.3.6.1.2.1.1.2");
	  
	  oldVbp = oldVbp->Next; // aka second varbind
	  if (NULL != oldVbp)
	  {
	    OidVarbind* oldOidVb2 = oldVbp->OIDVarbind();
	    oldOidVb2->Value("1.3.6.1.2.1.2.2.1.2");
	  }
	  
	  int sendlen = udp.Send(&p);
	  cout << "sent " << sendlen << " bytes" << endl;
	  printf("Packet sent\n");
	  
	  r = udp.Receive();
	  // note: if r is null, check the error code
	  if (r == NULL)
	  {
	    printf("No packet received\n");
	    long x = udp.ErrorCode();
	    printf("Error: %u\n", x);
	    return 0;
	  }
	  
	  printf("Packet received\n");
	  
	  // an errorcode of 10040 (WSAEMSGSIZE) means your buffer (ReadBufferSize) wasn't big enough
	  len = udp.ReadLength();
	  
	  cout << "read <" << len << "> bytes" << endl;
	  
	  SnmpParser parser((unsigned char*)r, len);
	  Packet* gPacket = parser.packet();
	  if (NULL != gPacket)
	  {
	    OutputPacket(gPacket);
	  } // if (NULL != gPacket)
	  /////////////////// end of second request	  
	}

	WSACleanup();

	return 0;
}

void
OutputPacket(Packet* gPacket)
{

  cout << "Length: " << gPacket->TotalLength() << endl;
  int version = gPacket->Version();
  cout << "Version: ";
  if (version == 0)
    cout << "SNMPv1";
  else
    if (version == 1)
      cout << "SNMPv2";
  cout << endl;
  
  cout << "Community: " << gPacket-> Community() << endl;
  
  if (version == 0)
  {
    cout << "Generic: " << gPacket->GenericTrapType() << endl;
    cout << "Specific: " << gPacket->SpecificTrapType() << endl;
    
    int tTime = gPacket->TimeTicks();
    tTime /= 100;
    int days = tTime/(60*60*24);
    tTime -= days * (60*60*24);
    int hrs = tTime/(60*60);
    tTime -= hrs*(60*60);
    int mins = tTime/(60);
    tTime -= mins*(60);
    char newcTime[128];
    sprintf(newcTime, "%d days %02dh:%02dm:%02ds", days, hrs, mins, tTime);
    cout << "TimeStamp: " << newcTime << " (" << gPacket->TimeTicks() << ")" << endl;
    
    cout << "SenderIP: " << gPacket->SenderIP() << endl;
  }
  
  if (version == 0)
    cout << "SenderOID: " << gPacket->SenderOID() << endl;



  VarbindList* vbl = gPacket->VbList();
  VbPair* vbp = vbl->FirstVbPair();
  int x = 1;

  while (NULL != vbp)
  {
    
    cout << "Varbind Number " << x++ << ' ' << endl;
    
    OidVarbind* oid = vbp->OIDVarbind();
    Varbind* v = vbp->VarBind();
    
    if (NULL != oid)
      cout << '\t' << "Oid: " << oid->Printable() << endl;
    
    if (NULL != v)
    {
      cout << '\t' << "Type: " << v->TypeString() << endl;
      cout << '\t' << "Data: " << v->Printable() << endl;
    }
    vbp = vbp->Next;
  }
  cout << endl << endl;

  // and the hex dump
  unsigned int l = gPacket->TotalLength();
  unsigned char* pdu = new unsigned char[l];
  gPacket->Build(pdu);
  for (unsigned int fmt = 0; fmt < l; fmt++)
  {
    if (fmt && !(fmt % 10))
      printf("\n");
    printf("%02x ", pdu[fmt]);
  }
  printf("\r\n");

  delete [] pdu;

}
