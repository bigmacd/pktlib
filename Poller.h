#define __POLLER_H__

#include "UdpClient.h"
#include "vbs.h"
#include "Thread.h"

typedef void (*PollerCallback)(Packet*);

#include <vector>
#include <string>
using namespace std;

class Poller : public Thread
{

  private:

    UdpClient             mClient;
    char                  mCommunity[64];  // of host to poll
    char                  mIpAddress[64];  // of host to poll
    int                   mPort;

    std::vector<string>   mOids;
    int                   mNumberOfOids;

    int                   mInterval;

    PollerCallback        mCallbackPtr;
    
    virtual void          main();
    
  protected:
    
    
  public:
    
    Poller();
    ~Poller();
    
    const char*  Host();    
    void         Host(const char* host);

    int          Port();
    void         Port(int p);

    const char*  Community();
    void         Community(const char* community);

    int          NumberOfOids();
    void         AddOid(const char* oid);

    void         Interval(int seconds);

    void         SetCallback(PollerCallback cbPtr);

    virtual void ProcessResponse(Packet* p) {};

};

#endif
