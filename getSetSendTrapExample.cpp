#include "vbs.h" 
#include "UdpClient.h" 
 
int  main(int argc, char** argv); 
void SendAuthenticationFailureTrap(char* destination);
void SetValues(Packet* retP);
void GetValues(Packet* retP);

int main(int argc, char** argv) 
{ 
#ifdef _WIN32 
  WSAData w; 
  WSAStartup(0x101, &w); 
#endif 
 
  if (argc != 2) 
  { 
    cout << "Need port number to listen for SNMP requests on" << endl; 
    return 1; 
  } 

  while (1)
  {
    UdpServer udp(atoi(argv[1]));
    udp.Timeout(0);  // timeout of zero blocks

    // the zero as a parameter to Receive has no meaning 
    Packet* retP = udp.Receive(0); 

    if (retP)
    { 

      int listLen = retP->VbListLength();

      // see what the request is
      if (retP->Type() == V1GETCOMMAND)
      {
	// it's a get, now get what?
#ifdef __DEBUG
	for (int x = 1; x <= listLen; x++)
	{
	  char* oid = retP->VbOID(x);
	  char* data = retP->VbData(x);
	  char* typeS = retP->VbType(x);
	  cout << "received a get for:" << endl;
	  cout << "\tOID: <" << oid << ">" << endl;
	  cout << "\tdata: <" << data << ">" << endl;
	  cout << "\ttype: <" << typeS << ">" << endl << endl;
	}
#endif
	GetValues(retP);
	retP->MakeResponse();
	udp.Send(retP);
      }
      else
      {
	if (retP->Type() == V1SETCOMMAND)
	{
	  // it's a set, a set on what?
#ifdef __DEBUG
	  for (int x = 1; x <= listLen; x++)
	  {
	    char* oid = retP->VbOID(x);
	    char* data = retP->VbData(x);
	    char* typeS = retP->VbType(x);
	    cout << "received a get for:" << endl;
	    cout << "\tOID: <" << oid << ">" << endl;
	    cout << "\tdata: <" << data << ">" << endl;
	    cout << "\ttype: <" << typeS << ">" << endl << endl;
	  }
#endif
	  // here you would check for authorization
	  if (!strcmp("private", retP->Community()))
	    SendAuthenticationFailureTrap("192.168.100.130");
	  
	  SetValues(retP);
	  retP->MakeResponse();
	  udp.Send(retP);

	} // if (retP->Type() == V1SETCOMMAND)
      }
    } // if (retP)
    Sleep (5000); //  aren't we all tired? 
  } // while (1)
}

void 
SendAuthenticationFailureTrap(char* destination)
{
  // can also do V2 traps 
  Packet tPacket(V1TRAP);  

  // set the community 
  tPacket.Community("public"); 

  // set the sender oid field  
  tPacket.SenderOID("1.3.6.1.4.1.6.1.311"); 
  
  // set the timeticks field - this is not the real value that should go here
  tPacket.TimeTicks(time(0));  

  // set the generic type (6 is enterprise specific)   
  tPacket.GenericTrapType(6);  
 
  // set the specific type (depends on one's own mib) 
  tPacket.SpecificTrapType(200);  

  // figure out the ip address 
  char* senderIP = NULL; 
  unsigned long len = 255; 
  char  buf[len]; 
  memset(buf, 0, len); 
  gethostname(buf, len); 

  HOSTENT* h = gethostbyname(buf); 
  if (h != NULL)  
  { 
    struct in_addr in; 
    memcpy(&in.s_addr, *(h->h_addr_list), sizeof(in.s_addr));  
    senderIP = inet_ntoa(in); 
  } 
  else // have to default it to something 
   senderIP =  "240.30.20.10"; 

  tPacket.SenderIP(senderIP); 

  // send it
  UdpClient udp(162, destination);
  udp.Send(&tPacket); 
}  


void 
GetValues(Packet* retP)
{
  // retrieve the values one by one
  int len = retP->VbListLength();
  VarbindList* vbl = retP->VbList();
  VbPair* vbp = vbl->FirstVbPair();

  int index = 1;
  BOOL notDone = TRUE;

  while (notDone)
  {

    OidVarbind* oid = vbp->OIDVarbind();
    Varbind*    vb  = vbp->VarBind();

    switch (vb->Type())
    {
      case (STRINGTAG):
      {
	delete vb;
	// you would really use the oid* to determine which string!
	vb = new StringVarbind("my String");
	vbp->VarBind(vb);
	break;
      }
      case (INTEGERTAG):
      {
	delete vb;
	// you would really use the oid* to determine which integer!
	vb = new IntVarbind(99);
	vbp->VarBind(vb);
	break;
      }

      // other cases go here like GAUGE32...see SnmpTypes.h


      default:
      {
	retP->ErrorStatus(NOSUCHNAME);
	retP->ErrorIndex(index);
	notDone = FALSE;
	break;
      }
    } // switch (vb->Type())

    index++;
    vbp = vbp->Next;
    if (vbp == NULL)
      notDone = FALSE;
  } // while (vbp != NULL)
}

void 
SetValues(Packet* retP)
{
  // set is usually a two pass operation, one for validation and
  // once for commit
  for (int commit = 0; commit < 2; commit++)
  {
    VarbindList* vbl = retP->VbList();
    VbPair* vbp = vbl->FirstVbPair();
    int index = 1;
    while (vbp != NULL)
    {
      OidVarbind* oid = vbp->OIDVarbind();
      Varbind*    vb  = vbp->VarBind();
      if (commit)
      {
      }
      else
      {
      }

      index++;
      vbp = vbp->Next;
    } // while (vbp != NULL)
  }
}


