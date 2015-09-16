//I have adhered to the Honor Code in this Assignment
//Evan Lowy, Axandre Oge, Miles Allen, Mike Ponz


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
#include <fcntl.h>

char HOST[100];
char PATH[100];
char FILE_NAME[100];

//#define getHost	"[^http:\/\/][^\/]*"
//#define getPath	"\b\/.*"
//#define getFile "[^\/]*$"


int main(int argc, char** argv) 
{	
	
	char* url = argv[1];
	sscanf( url, "http://%[^/]%s", HOST, PATH);

	
	if (strcmp(PATH, "") == 0) {
		strcpy(FILE_NAME, "index.html");
	}
	else {
		strcpy(FILE_NAME, strrchr( PATH, '/'));
	}
	
		
	struct addrinfo hints;
	struct addrinfo *ip, *results;
	// Things we had to add on the fly
	//void *addr;
	//struct sockaddr_in *ipv4 = (struct sockaddr_in *)ip->ai_addr;
	//addr = &(ipv4->sin_addr);
	//char ipstr[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype= SOCK_STREAM;
	int ipAddress;
	ipAddress =  getaddrinfo(HOST, "80", &hints, &results);
	
	//inet_ntop(ip->ai_family, addr, ipstr, sizeof(ipstr)); 
	//printf("%s", &ip);
	
	

	ip=results;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0) {
		perror("Creating socket failed: ");
		exit(1);
	}
	
	struct sockaddr_in addr; 	// internet socket address data structure
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);    // byte order is significant
	
	int res = connect(sock, ip->ai_addr, ip->ai_addrlen);
	if(res < 0) {
		perror("Error connecting: ");
		exit(1);
	}
	freeaddrinfo(results);

	char request[1000];
	sprintf(request, "GET %s HTTP/1.0\r\n\r\n", PATH);
	printf("%s\n", request);
	int len = strlen(request);
	send(sock, request, len, 0);
	char buf[1024*1024];
	memset(&buf,0,sizeof(buf));
	int recv_count = recv(sock, buf, 1024*1024, 0);
	if(recv_count<0) { perror("Receive failed");	exit(1); }

	char *cde = strstr( buf, " ");
	int code = 0;
	int stupid = 100;
	for (int i = 0; i < 3; i++){
		cde++;
		code = code + ((*cde - '0') * stupid);
		stupid=stupid/10;
	}
	if (code != 200){
		printf("Got Error Code: %d", code);
		exit(1);
	}
																
	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *filename = FILE_NAME;
	
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);	
	char *ptr = buf;
	int offset=0;
	for (int i = 0; i < 1024; i++){
		if (*ptr == '\r'){
			if (*ptr+1 == '\n'){
				if (*ptr+2 == '\r'){
					if (*ptr+3 == '\n'){
						ptr= ptr +4;
						offset= offset+4;
						break;
					}
				}
			}
		}
		ptr++;
		offset++;	
	}
	write(fd, ptr, (sizeof(buf) - offset));
	close(fd);	
	shutdown(sock,SHUT_RDWR); 
	
	
	
}
