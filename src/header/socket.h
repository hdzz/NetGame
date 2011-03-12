#ifndef SOCKET_H
#define SOCKET_H

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
	#define PLATFORM PLATFORM_WINDOWS

#elif defined(__APPLE__)
	#define PLATFORM PLATFORM_MAC

#else
	#define PLATFORM PLATFORM_UNIX

#endif

#if PLATFORM == PLATFORM_WINDOWS

	#include <winsock2.h>
	#pragma comment( lib, "wsock32.lib" )

#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

	#include <unistd.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>

#else

	#error unknown platform!

#endif



#include <string.h>
#include <assert.h>
#include <stdio.h>

//this is here simply for the unistd include.

inline bool InitializeSockets()
{
	#if PLATFORM == PLATFORM_WINDOWS
   	WSADATA WsaData;
	int error = WSAStartup(MAKEWORD(2,2), &WsaData);
	return (error != 0);
	#else
	return true;
	#endif
}

inline void ShutdownSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSACleanup();
#endif
}

#include "address.h"

namespace net
{

class Socket
{
public:

	Socket();
	~Socket();
	bool Open(unsigned short port);
	void Close();
	bool IsOpen() const;
	bool Send(const address & destination, const void * data, int size);
	int Receive(address & sender, void * data, int size);

private:

	int socket;
};

}

#endif//SOCKET_H
