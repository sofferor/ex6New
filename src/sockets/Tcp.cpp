

/************************************************************
* File description: TCP implementation.						*
* the class inherit from socket. 							*
* methods of tcp socket type								*
************************************************************/

#include "Tcp.h"

/***********************************************************************
* function name: Tcp												   *
* The Input: Boolean, true - if server, false if client	and port number*
* The output: none										               *
* The Function operation: creating new Tcp. initialize if server and   *
* port_num by the input												   *
***********************************************************************/
Tcp::Tcp(bool isServers, int port_num) {
	this->port_number = port_num;
	this->isServer = isServers;

}

/***********************************************************************
* function name: ~Tcp												   *
* The Input: none													   *
* The output: none										               *
* The Function operation: default destructor					       *
***********************************************************************/
Tcp::~Tcp() {
	// TODO Auto-generated destructor stub
}

/***********************************************************************
* function name: initialize											   *
* The Input: none              										   *
* The output: 1 success or 0 failed error type will print              *
* The Function operation: initialize the Socket object by getting	   *
* socket descriptor. bind and accept for servers or connect for clients*
***********************************************************************/
int Tcp::initialize() {
	//getting a socket descriptor and check if legal
	this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); // (IPv4 , TCP, flags) --> Socket Descriptor
	if (this->socketDescriptor < 0) {
		//return an error represent error at this method
		perror("ERROR_SOCKET - in initialize()\n");
		return 0;
	}
	//if server
	if (this->isServer) {
		//initialize the struct
		struct sockaddr_in sin;                     // ipv4 socket address structure
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;                   // IPv4 version
		sin.sin_addr.s_addr = INADDR_ANY;           // binds to all ip address of the host
		sin.sin_port = htons(this->port_number);    // pass ServerRun Post number

		//bind
		if (::bind(this->socketDescriptor,(struct sockaddr *) &sin, sizeof(sin)) < 0) {
			//return an error represent error at this method
			perror("ERROR_BIND - in initialize()\n");
			return 0;
		}
		//listen
		if (listen(this->socketDescriptor, this->backLog) < 0) {
			//return an error represent error at this method
			perror("ERROR_LISTEN - in initialize()\n");
			return 0;
		}
		// start to accept first client (get 0 if failed)

		//if client
	} else {
		struct sockaddr_in sin;                                          // ipv4 socket address structure
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;                                        // IPv4 version
		sin.sin_addr.s_addr = inet_addr((this->ip_address).c_str());     // get IP address from DEFINE IP number
		sin.sin_port = htons(this->port_number);                         // pass port number
		if (connect(this->socketDescriptor,
					(struct sockaddr *) &sin, sizeof(sin)) < 0) {
			//return an error represent error at this method
			perror("ERROR_CONNECT - in initialize()\n");
			return 0;
		}
		// success client initialize

	}
	//return correct if there were no problem
	return 1;

}






/***********************************************************************
* function name: acceptClient								    	   *
* The Input: None                                                      *
* The output: positive integer in case of success or negetive integer  *
*       if it fails.                                                   *
* The Function operation: getting a unique int from the socket,	       *
*                   and returning it.	    						   *
***********************************************************************/
int Tcp::acceptClient(){
	int descriptorCommunicateClient = 0;
	struct sockaddr_in client_sin;
	unsigned int addr_len = sizeof(client_sin);
	descriptorCommunicateClient = accept(this->socketDescriptor,
							  (struct sockaddr *) &client_sin, &addr_len);
	if (descriptorCommunicateClient < 0) {
		//return an error represent error at this method
		perror("ERROR_CONNECT - in acceptClient()\n");
		exit(1);
	}
	return descriptorCommunicateClient;
}






/***********************************************************************
* function name: sendData											   *
* The Input: string data to send and descriptor Communicate of Client  *
*     in server case or any number in Client case.                     *
* The output: number of bytes that gets                 	           *
* The Function operation: sending the required data, using his length  *
* and the socket descriptor or client descriptor.					   *
***********************************************************************/
int Tcp::sendData(string data, int clientDescriptor) {
	size_t data_len = data.length();
	const char * datas = data.c_str();
	ssize_t sent_bytes = send(this->isServer ? clientDescriptor : this->socketDescriptor, datas, data_len, 0);
	if (sent_bytes < 0) {
		string host = "";
		if (isServer) {
			host = "ServerRun\n";
		} else {
			host = "Client\n";
		}
		host = "ERROR_SEND - in sendData() on " + host;
		//return an error represent error at this method
		perror(host.c_str());
	}
	//return correct if there were no problem
	return sent_bytes;
}

/***********************************************************************
* function name: receiveData										   *
* The Input: buffer to send and is size, and also - descriptor         *
*   Communicate Client in server case or any number in client case     *
* The output: int number representing the return status	               *
* The Function operation: getting data from the other socket to,	   *
* enter it to the buffer and print the data							   *
***********************************************************************/
int Tcp::receiveData(char* buffer, int size, int clientDescriptor) {
	ssize_t read_bytes = recv(this->isServer ? clientDescriptor : this->socketDescriptor, buffer, size, 0);
	//checking the errors
	if (read_bytes <= 0) {
		string host = "";
		if (isServer) {
			host = "ServerRun\n";
		} else {
			host = "Client\n";
		}
		if (read_bytes == 0) {
			host = "CONNECTION_CLOSED - in receiveData() on " + host;
			perror(host.c_str());
			exit(1);
		} else {
			host = "ERROR_RECEIVE - in receiveData() on " + host;
			//return an error represent error at this method
			perror(host.c_str());
			exit(1);
		}
	}
	//return correct if there were no problem
	return read_bytes;
}

void Tcp::setIp_address(string ipAdr) {
	this->ip_address = ipAdr;
}
