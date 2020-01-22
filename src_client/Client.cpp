#include "Client.h"


Client::Client() {

}

Client::~Client() {

}

void Client::connectTo(const char *ip_addr, unsigned short port){}
void Client::handleConnection() {}
void Client::closeConn() {}

/*
The server should be a single-process non-blocking server that can accept multiple concurrent connections and handle user input.
When the user first connects, they should receive a list of possible commands and what those commands do. These should include

hello - displays a greeting (student's choice)
1, 2, 3, 4, 5 - displays information to the user (student's choice, but each number should provide different info)
passwd - Does nothing yet, but in HW2, will allow them to change their password
exit - disconnects the user
menu - should display the list of available commands in a clean, readable format
Commands not on this list should display an error message.

Students should NOT change server_main.cpp, client_main.cpp, Server.cpp, Client.cpp or associated header files.
When the code is graded, your copy of those files will not be used. If you made changes to them, your code may not compile with the
original version and this will result in a reduced grade.
*/


