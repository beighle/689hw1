#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <string>

//jb
#include <iostream>
#include <sstream>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//#include "exceptions.h"

//endjb
#include "Client.h"

#define SOCKET_ERROR (-1) //jb

using namespace std;//jb

// The amount to read in before we send a packet
const unsigned int stdin_bufsize = 50;
const unsigned int socket_bufsize = 100;

class TCPClient : public Client
{
public:
   TCPClient();
   ~TCPClient();

   virtual void connectTo(const char *ip_addr, unsigned short port);
   virtual void handleConnection();

   virtual void closeConn();

private:
   int s0;
   int res;
};


#endif
