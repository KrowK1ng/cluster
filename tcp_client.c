#include<stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(int args, char* argv[]){
	// create a socket
	int network_socket;
	network_socket = socket(	AF_INET, 	SOCK_STREAM,	0);

	// connect to server
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int cstatus = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	if (cstatus == -1){
		printf("No connection :(");
		return 0;
	}


	return 0;
}
