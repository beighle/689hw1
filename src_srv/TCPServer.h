#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "exceptions.h"

#include "Server.h"

using namespace std;

#define SOCKET_ERROR (-1) //jb

class TCPServer : public Server 
{
public:
   TCPServer();
   ~TCPServer();

   void bindSvr(const char *ip_addr, unsigned short port);
   void listenSvr();
   void shutdown();


private:
   int s0, s1;
   int res;
};


#endif
