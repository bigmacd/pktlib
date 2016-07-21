#ifndef  __POLLER_H__
#include "Poller.h"
#endif

#include <string>

Poller::Poller()
       :Thread("Poller"),
	mCallbackPtr(NULL),
	mNumberOfOids(0),
	mInterval(5000)
{
  //  for (int i = 0; i < 32; i++)
  //    mOids[i] = NULL;
  mOids.clear();
}

Poller::~Poller()
{
  int x = 0;
  //  while (mOids[x] != NULL && x < 32)
  //    delete mOids[x++];
  mOids.clear();
}

const char*  
Poller::Host()
{
  return mIpAddress;
}

void         
Poller::Host(const char* host)
{
  memset(mIpAddress, 0, 64);
  if (host != NULL)
#ifdef _WIN32
    strncpy_s(mIpAddress, host, 63);
#else
    strncpy(mIpAddress, host, 63);
#endif
}

int          
Poller::Port()
{
  return mPort;
}

void         
Poller::Port(int p)
{
  mPort = p;
}

const char*  
Poller::Community()
{
  return mCommunity;
}

void         
Poller::Community(const char* community)
{
  memset(mCommunity, 0, 64);
  if (community != NULL)
#ifdef _WIN32
    strncpy_s(mCommunity, community, 63);
#else
    strncpy(mCommunity, community, 63);
#endif
}

void         
Poller::SetCallback(PollerCallback cbPtr)
{
  mCallbackPtr = cbPtr;
}

int          
Poller::NumberOfOids()
{
  return mNumberOfOids;
}

void         
Poller::AddOid(const char* oid)
{
  std::string sOid = oid;
  //  mOids.push_back(oid);
  mOids.push_back(sOid);
  //  if (mNumberOfOids < 32)
  //    if (oid != NULL)
  //    {
  //      mOids[mNumberOfOids] = strdup(oid);
  mNumberOfOids++;
  //    }
}

void
Poller::Interval(int seconds)
{
  mInterval = seconds * 1000;
}

void 
Poller::main()
{
  // this allows a pause because posix threads start running
#ifndef __WIN32
  while (Thread::State() == STOPPED);
#endif

  mClient.Port(mPort);
  mClient.Host(mIpAddress);

  Packet p(V1GETCOMMAND);
  p.Community(mCommunity);

  std::vector<string>::iterator i = mOids.begin();
  for (; i < mOids.end(); i++)
    //  for (int x = 0; x < mNumberOfOids; x++)
  {
    std::string oid = *(i);
    OidVarbind* o = new OidVarbind((char*)(oid.c_str()));
    //    OidVarbind* o = new OidVarbind(mOids[i]);
    VbPair* vbp = new VbPair(o, NULL);
    p.Add(vbp);
  }

#ifdef __WIN32  
  while (Thread::State() != threadState::TERMINATED)
#else
  while (Thread::State() != TERMINATED)
#endif
  {
    // stupid posix threads don't suspend
#ifndef __WIN32
    if (Thread::State() == STOPPED)
    {
      Sleep(1000);
      continue;
    }
#endif
    mClient.Send(&p);
    Packet* retP = mClient.Receive(0);

    if (mCallbackPtr == NULL)
      ProcessResponse(retP);
    else
      (*mCallbackPtr)(retP);
    Sleep(mInterval);
  }
}

