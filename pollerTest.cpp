// to build on Solaris with gcc:
// gcc -g -D_SOLARIS -I. -I../pktlib pollerTest.cpp -o pltest -L../pktlib -lPktLib -L/usr/local/lib -lstdc++ -lsocket -lnsl -lpthread


// to build on Linux with gcc:
// gcc -=g -D_LINUX -O2 -I. -I../pktlib pollerTest.cpp -o pltest -L../pktlib -lPktLib -lstdc++ -lnsl -lpthread



#include <iostream.h>
#include "Poller.h"

static int me = 0;

class myPoller : public Poller
{
  public:
    int  numberOfPolls;
    myPoller() { numberOfPolls = 0; }
    ~myPoller() {};

    void ProcessResponse(Packet* p) // this is the "callback"
    { 
      while (me);  // just pretties up the printout
      me = 1;
      cout << "in myPoller::ProcessResponse" << endl;
      if (p != NULL)
      {
	numberOfPolls++;
	int len = p->VbListLength();
	cout << "list len is " << len << endl;
	for (int x = 1; x <= len; x++)
	{
	  cout << "vboid: " << p->VbOID(x) << endl;
	  cout << "vbtype: " << p->VbType(x) << endl;
	  cout << "vbdata: " << p->VbData(x) << endl;
	}
	cout << endl;
      }
      else
	cout << "myPoller:p is null" << endl;
      me = 0;
    }
};

void myCallback(Packet* p)
{
  // standard C type callback
  while (me); // just pretties up the printout
  me = 1;
  cout << "in my call back" << endl;

  if (p != NULL) // ya never know, and if you think you do then
  {              // put down that editor and back away slowly
    int len = p->VbListLength();
    cout << "list len is " << len << endl;
    for (int x = 1; x <= len; x++)
    {
      cout << "vboid: " << p->VbOID(x) << endl;
      cout << "vbtype: " << p->VbType(x) << endl;
      cout << "vbdata: " << p->VbData(x) << endl;
    }
    cout << endl;
  }
  else
    cout << "mycallback: p is null" << endl;
  me = 0;
}


void
main(void)
{

#ifdef __WIN32
  WSAData d;
  WSAStartup(0x101, &d);
#endif

  cout << "creating poller p" << endl;
  Poller p;
  p.Host("192.168.1.9");
  p.Port(161);
  p.Community("public");
  p.SetCallback((PollerCallback)myCallback);
  p.AddOid("1.3.6.1.2.1.1.1.0");
  p.AddOid("1.3.6.1.2.1.1.2.0");
  p.Interval(6); // seconds
  cout << "starting poller p" << endl;
  p.Start();

  cout << "creating poller mp" << endl;
  myPoller mp;
  mp.Host("192.168.1.9");
  mp.Port(161);
  mp.Community("public");
  mp.AddOid("1.3.6.1.2.1.1.3.0");
  mp.AddOid("1.3.6.1.2.1.1.4.0");
  mp.Interval(10); // seconds
  cout << "starting poller mp" << endl;
  mp.Start();

  while(1)
  {
    Sleep(10000); // in milliseconds, see compat.h
    if (mp.numberOfPolls >= 10)
    {
      mp.Stop();
    }
  }    

#ifdef __WIN32
  WSACleanup();
#endif
}

