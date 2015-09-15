#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <regex.h>
#include <netdb.h>
#include <arpa/inet.h>


char HOST[100] = "www.google.com";
char PATH[100] = "intl/web/test.html";
char FILE_NAME[100];

//#define getHost	"[^http:\/\/][^\/]*"
//#define getPath	"\b\/.*"
//#define getFile "[^\/]*$"


int main(int argc, char** argv) 
{	
	/*
	char* url = argv[1];
	sscanf( url, "http://%[^/]", HOST);
	strcpy(PATH, strrchr(
	//sscanf( url, "%[^/]*$", FILE_NAME);
	*/
	if (strcmp(PATH, "") == 0) {
		strcpy(FILE_NAME, "index.html");
	}
	else {
		strcpy(FILE_NAME, strrchr( PATH, '/'));
	}
	
	printf("%s %s %s", HOST, PATH, FILE_NAME);
	
	struct addrinfo hints;
	struct addrinfo *ip;
	
	// Things we had to add on the fly
	void *addr;
	struct sockaddr_in *ipv4 = (struct sockaddr_in *)ip->ai_addr;
	addr = &(ipv4->sin_addr);
	char ipstr[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype= SOCK_STREAM;
	int ipAddress;
	ipAddress =  getaddrinfo(HOST, "80", &hints, &ip);
	
	inet_ntop(ip->ai_family, addr, ipstr, sizeof(ipstr)); 
	printf("%s", ipstr);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0) {
		perror("Creating socket failed: ");
		exit(1);
	}
	
	//struct sockaddr_in addr; 	// internet socket address data structure
	//addr.sin_family = AF_INET;
	//addr.sin_port = htons(8080);    // byte order is significant
	//addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	
	//int res = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	//if(res < 0) {
	//	perror("Error connecting: ");
	//	exit(1);
	//}

	/*
	char buf[255];
	memset(&buf,0,sizeof(buf));
	int recv_count = recv(sock, buf, 255, 0);
	if(recv_count<0) { perror("Receive failed");	exit(1); }

	*/																						

	shutdown(sock,SHUT_RDWR); 
}
