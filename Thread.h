#define __THREAD_H__

#ifdef _WIN32
#include "Security.h"
#else
#include <pthread.h>
#endif

class Thread
{
  public:

#ifdef _WIN32
    typedef enum
    {
      ABOVENORMAL =  THREAD_PRIORITY_ABOVE_NORMAL,
      BELOWNORMAL =  THREAD_PRIORITY_BELOW_NORMAL,
      HIGHEST =      THREAD_PRIORITY_HIGHEST,
      IDLE =         THREAD_PRIORITY_IDLE,
      LOWEST =       THREAD_PRIORITY_LOWEST,
      NORMAL =       THREAD_PRIORITY_NORMAL,
      TIMECRITICAL = THREAD_PRIORITY_TIME_CRITICAL
    } threadPriority;
#endif

    typedef enum
    {
      STARTED = 0,
      PAUSED,
      STOPPED,
      TERMINATED
    } threadState;
    
  private:

#ifdef _WIN32
    HANDLE                mThreadId;
    threadPriority        mPriority;
#else
    pthread_t             mThreadId;
#endif


    Thread(const Thread&){};

    threadState           mState;
    char                  mName[32];

  protected:



  public:

    Thread(char* name = "Simple");
#ifdef _WIN32
    Thread(const Security* security, threadPriority prio = NORMAL);
#endif
    ~Thread();
  
    void Start();
    void Stop();
    void Exit();
    virtual void main() = 0;

#ifdef _WIN32
    HANDLE        ThreadId();
#else
    pthread_t     ThreadId();
#endif

#ifdef _WIN32
    threadPriority        Priority();
    void                  Priority(threadPriority prio);
#endif

    threadState           State();
    void                  State(threadState state);

};

#endif
