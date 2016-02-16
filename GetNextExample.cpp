#define ipAddressOid "1.3.6.1.2.1.4.20.1.1"

unsigned int 
privNumberOfIpAddresses()
{
  unsigned int retVal = 0;
  bool         done   = false;

  int request = getpid();

  // set up the packet, like always
  Packet packet(V1GETNEXTCOMMAND);
  packet.Community(mCommunity);
  packet.RequestId(request);  

  char oidstring[128];
  memset(oidstring, 0, 128);
  sprintf(oidstring, "%s.%d", ipAddressOid, 0);

  OidVarbind* oid = new OidVarbind(oidstring);

  VbPair* vbp = new VbPair(oid, NULL);
  packet.Add(vbp);

  // this guy handles the udp communications
  UdpClient mClient(161, "somehost");

  while (!done)
  {
    mClient.Send(&packet);
    Packet* retP = mClient.Receive(0);
    // check the response to our get next
    // first, make sure it was our request
    if (retP && retP->RequestId() == request)
    {
      // make sure there was no error
      if ((mPollStatus = retP->ErrorStatus()) == NOERROR)
      {
	// examine the OID returned to us
	const char* nextOid = retP->VbOID(1);
	// when the getnext leaves the IP address OID range
	// (ipAddressOid),  we are done.
	if (!strncmp(ipAddressOid, nextOid, strlen(ipAddressOid)))
	{
	  // set up for the next getnext - use the OID returned
	  // in our last request and replace to OID in our 
	  // packet
	  sprintf(oidstring, "%s", nextOid);
	  delete oid;
	  oid = new OidVarbind(oidstring);
	  packet.VbList()->FirstVbPair()->OIDVarbind(oid);
	  // since we are still in the range, count it
	  retVal++;
	}
	else
	  // we have left the range if ipAddressOID, so
	  // we are done.
	  done = true;
      }
      delete retP;  
    }
    else
    {
      // some error, examine it more carefully
      done = true;
      mPollStatus = TIMEDOUT;
    }
  }
  return retVal;
}
