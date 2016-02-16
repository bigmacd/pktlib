#include "Thread.h"
#endif

#ifdef _WIN32
#include <process.h>
#endif

#include <string.h>

#ifdef _WIN32
long 
EhFilter(LPEXCEPTION_POINTERS exPtrs)
{
//    cout << "in EhFilter" << endl;
    DWORD code = exPtrs->ExceptionRecord->ExceptionCode;
//    cout << "code is " << code << endl;
    return 0L;
}
#endif

#ifdef _WIN32
long WINAPI
#else
void*
#endif
ThreadProc(void* thisPtr)
{
  //  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)
  //			      EhFilter);

  try
  {
#ifdef _LINUX
    while (((Thread*)thisPtr)->State() == Thread::STOPPED);
#endif
    ((Thread*)thisPtr)->main();  
  }
  catch (...)
  {}

  return 0L;
}

Thread::Thread(char* name)
       :mThreadId(0),
#ifdef _WIN32
        mPriority(NORMAL),
#endif
	mState(STOPPED)
{
  memset(mName, 0, 32);
#ifdef _WIN32
  strncpy_s(mName, name, 31);
#else
  strncpy(mName, name, 31);
#endif

#ifdef _WIN32
  unsigned long id;
  mThreadId = 
    ::CreateThread(NULL,
		   0,
		   (LPTHREAD_START_ROUTINE)ThreadProc,
		   (void*)this,
		   CREATE_SUSPENDED,
		   &id);
  ::SetThreadPriority(mThreadId, mPriority);
#else
  ::pthread_create(&mThreadId,
		   NULL,
		   ThreadProc,
		   this);
#endif
}

#ifdef _WIN32
Thread::Thread(const Security* security, threadPriority prio)
       :mThreadId(0),
        mPriority(prio),
	mState(STOPPED)
{
  unsigned long id;
  SECURITY_ATTRIBUTES sa = security->SecurityAttributes();

  mThreadId = ::CreateThread(&sa,
			     0,
			     (LPTHREAD_START_ROUTINE)ThreadProc,
			     (void*)this,
			     CREATE_SUSPENDED,
			     &id);

  ::SetThreadPriority(mThreadId, mPriority);
}
#endif

Thread::~Thread() 
{
  Exit();
#ifdef _WIN32
  ::CloseHandle(mThreadId);
#endif
}

void
Thread::Start(void)
{
  mState = STARTED;
#ifdef _WIN32
  ::ResumeThread(mThreadId);
#endif
}

void
Thread::Stop(void)
{
  mState = STOPPED;
#ifdef _WIN32
  ::SuspendThread(mThreadId);
#endif
}

void
Thread::Exit(void)
{
  mState = TERMINATED;
}

#ifdef _WIN32
HANDLE
#else
pthread_t
#endif
Thread::ThreadId()
{
  return mThreadId;
}

#ifdef _WIN32
Thread::threadPriority        
Thread::Priority()
{
  return mPriority;
}

void                  
Thread::Priority(threadPriority prio)
{
  Stop();
  ::SetThreadPriority(mThreadId, prio);
  mPriority = prio;
  Start();
}
#endif

void                  
Thread::State(threadState state)
{
  // this is handled through state calls like Stop();
}

Thread::threadState        
Thread::State()
{
  return mState;
}







