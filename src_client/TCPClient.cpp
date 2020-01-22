#include "TCPClient.h"
#include "exceptions.h"

/**********************************************************************************************
 * TCPClient (constructor) - Creates a Stdin file descriptor to simplify handling of user input. 
 *
 **********************************************************************************************/

TCPClient::TCPClient() {
}

/**********************************************************************************************
 * TCPClient (destructor) - No cleanup right now
 *
 **********************************************************************************************/

TCPClient::~TCPClient() {
	closeConn();
}

/**********************************************************************************************
 * connectTo - Opens a File Descriptor socket to the IP address and port given in the
 *             parameters using a TCP connection.
 *
 *    Throws: socket_error exception if failed. socket_error is a child class of runtime_error
 **********************************************************************************************/

void TCPClient::connectTo(const char *ip_addr, unsigned short port) {

	s0 = socket(AF_INET, SOCK_STREAM, 0);
    if (s0 == SOCKET_ERROR)
    	throw socket_error("Error connecting to socket");

    struct sockaddr_in server;
    bzero( &server, sizeof( server ) );
    struct hostent *host = gethostbyname("localhost");

    server.sin_family = AF_INET;
    short peerPort = 5050;
    server.sin_port = htons(peerPort);

    //write resolved svr IP to address structure
    memmove(&(server.sin_addr.s_addr), host->h_addr_list[0], 4);

    // Connect to the remote server
    res = connect(s0, (struct sockaddr*) &server, sizeof(server));
    if (res == SOCKET_ERROR)
    	throw socket_error("Error connecting to remote server");

    std::cout << "Hello! You are now connected to the HAL knowledge server" << std::endl;

}

/**********************************************************************************************
 * handleConnection - Performs a loop that checks if the connection is still open, then
 *                    looks for user input and sends it if available. Finally, looks for data
 *                    on the socket and sends it.
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPClient::handleConnection() {
    string 	menu = "\n";
    		menu += "menu of commands: \n";
    		menu += "1: for special 1msg from svr \n";
    		menu += "2: for special 2msg from svr \n";
    		menu += "3: for special 3msg from svr \n";
    		menu += "4: for special 4msg from svr \n";
    		menu += "5: for special 5msg from svr \n";
    		menu += "menu: to see all commands \n";
    		menu += "passwd: to change password \n";
    		menu += "exit: to exit the client \n\n";

	while(1)
	{
		//send server msg
		string inpt;
		cout << "Type: menu [enter] for command options - or enter a known command now:\n";
		getline (cin, inpt);
		if (inpt == "menu")
			cout << menu;
		else if (inpt=="1" || inpt=="2" || inpt=="3" || inpt=="4" || inpt=="5")
		{
			inpt = inpt + "\r\n";
			const char *c = inpt.c_str();
			write(s0, c, 20);

			//read server response
			char buffer[4096];
			res = read(s0, buffer, 4095);
			if (res < 0)
			{
				std::cerr << "Error: " << strerror(errno) << std::endl;
				exit(1);
			}
			std::cout << "HAL Svr Response: " << buffer << "\n";
		}
		else if (inpt=="passwd")
			cout << "Password compromised! Reset = 1 bitcoin!\n";
		else if (inpt=="exit")
		{
			cout << "Thank You! Bye-bye...!\n";
			close(s0);
			break;
		}
		else
			cout << "Error: Try again! Enter legitimate command\n";

	}
}

/**********************************************************************************************
 * closeConnection - we're shutting it down
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPClient::closeConn() {
	res = close(s0);
    if (res == SOCKET_ERROR)
    	throw socket_error("Error: closing socket 0");

}


