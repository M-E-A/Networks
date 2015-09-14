#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

char HOST[100];
char PATH[100];
char FILE[100];

int main(int argc, char** argv) 
{	
	const char url = argv[1];
	sscanf( url, "%[^http:\/\/][^\/] %\b\/.*", HOST, PATH);
	//[^http:\/\/][^\/]* :how to get host 
	//\b\/.* :how to get path
	//[^\/]*$ : how to get file
	
	if (strcmp(PATH, '') == 0) {
		FILE='index.html';
	}
	else {
		FILE = strrchr( url, '/');
	}
	
	printf("%s %s %s", HOST, PATH, FILE);
	
	

/*
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0) {
		perror("Creating socket failed: ");
		exit(1);
	}
	
	struct sockaddr_in addr; 	// internet socket address data structure
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);    // byte order is significant
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	
	int res = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	if(res < 0) {
		perror("Error connecting: ");
		exit(1);
	}

	char buf[255];
	memset(&buf,0,sizeof(buf));
	int recv_count = recv(sock, buf, 255, 0);
	if(recv_count<0) { perror("Receive failed");	exit(1); }

	printf("%s",buf);																							

	shutdown(sock,SHUT_RDWR); */
}
