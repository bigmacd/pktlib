#define __COMPAT_H__

#include <stdio.h>

#ifdef _WIN32
  //#ifdef _AFXDLL

#ifdef _WINDOWS
#include <windows.h>
#else
#include <afxwin.h>
#endif

#else
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
//#ifdef _SOLARIS
//#include <stdint.h>
//#endif

#if defined(_LINUX)
typedef bool BOOL;
#endif

//typedef boolean_t bool;
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct hostent HOSTENT;

#ifdef _LINUX
typedef int64_t __int64;
#else
typedef long long __int64;
#endif

#define TRUE true
#define FALSE false
//#define false B_FALSE
//#define true B_TRUE
#define INVALID_SOCKET -1

#ifndef FIONBIO
#define FIONBIO O_NDELAY
#endif

#define WSAGetLastError() errno
#define ioctlsocket(a, b, c) fcntl(a, b, c)
#define closesocket(x) close(x)
#define stricmp(a, b) strcasecmp(a, b)
#define Sleep(x) sleep(x/1000)

#ifndef INADDR_NONE
#define INADDR_NONE -1
#endif

#endif


#endif
