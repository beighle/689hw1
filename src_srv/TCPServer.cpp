#include "TCPServer.h"

TCPServer::TCPServer() {

}


TCPServer::~TCPServer() {
	shutdown();
}

/**********************************************************************************************
 * bindSvr - Creates a network socket and sets it nonblocking so we can loop through looking for
 *           data. Then binds it to the ip address and port
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::bindSvr(const char *ip_addr, short unsigned int port) {

    s0 = socket(AF_INET, SOCK_STREAM, 0);
    if (s0 == SOCKET_ERROR)
    	throw socket_error("Error connecting to socket");

    struct sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(5050);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    res = bind(s0, (struct sockaddr*) &myaddr, sizeof(myaddr));
    if (res == SOCKET_ERROR)
    	throw socket_error("Error binding port");

    // Set "LINGER" timeout to 0, to close the socket at termination
    struct linger linger_opt = { 1, 0 }; //Linger active, timeout 0
    setsockopt(s0, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

    res = listen(s0, 1); // "1" = max queue length
    if (res == SOCKET_ERROR)
    	throw socket_error("Error trying to listen on port");

    //Accept conn. "accept" waits with no timeout limit...)
    struct sockaddr_in peeraddr;
    socklen_t peeraddr_len;
    s1 = accept(s0, (struct sockaddr*) &peeraddr, &peeraddr_len);
    if (s1 == SOCKET_ERROR)
    	throw socket_error("Error accepting client connection");

    //we have a client conn.
    std::cout << "Connection from IP "
              << ( ( ntohl(peeraddr.sin_addr.s_addr) >> 24) & 0xff ) << "."
              << ( ( ntohl(peeraddr.sin_addr.s_addr) >> 16) & 0xff ) << "."
              << ( ( ntohl(peeraddr.sin_addr.s_addr) >> 8) & 0xff )  << "."
              <<   ( ntohl(peeraddr.sin_addr.s_addr) & 0xff ) << ", port "
              << ntohs(peeraddr.sin_port);

}

/**********************************************************************************************
 * listenSvr - Performs a loop to look for connections and create TCPConn objects to handle
 *             them. Also loops through the list of connections and handles data received and
 *             sending of data.
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::listenSvr() {

	while(1)
	{
		//receive a msg
	    char buffer[4096];
	    res = read(s1, buffer, 4095);
	    if (res == SOCKET_ERROR)
	    	throw socket_error("Error: buffer read");
	    buffer[res] = 0;
	    string from_client = buffer;
	    std::cout << "Received from client: " << from_client;//<< res << " bytes: "

		//send a msg
	    string response = "SvrSay" + from_client + "\r\n";
	    write(s1, response.c_str(), 8);

		sleep(1);
	}
}

/**********************************************************************************************
 * shutdown - Cleanly closes the socket FD.
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::shutdown() {
    res = close(s0);
    if (res == SOCKET_ERROR)
    	throw socket_error("Error: closing socket 0");

    res = close(s1);
    if (res == SOCKET_ERROR)
    	throw socket_error("Error: closing socket 1");

}
