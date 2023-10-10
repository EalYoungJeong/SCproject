///////////////////////////////////////////////////////////////////////
// File Name		: cli.c			             	     //
// Date			: 2021/4/28			             //
// Os 			: Ubuntu 16.04 LTS 64bits	   	     //
// Author 		: Jeong Eal Young		             //
// Student ID		: 2016722033				     //
// ----------------------------------------------------------------- //
// Title : System Programing Assignment #2-1			     //
// Description : This assignment is about implementing server-client //
// and socket programing. In this code, this program becomes a client//
// and requests a connection to the server. When request accepted,   //
// client send input url to server and receive hit or miss from      //
// server. When bye input, this program ends			     //
///////////////////////////////////////////////////////////////////////
// int connect(int sockfd, const struct sockaddr *servaddr, socket_t //
//							     addrlen)//
// ================================================================= //
// Input : int sockfd : return of calling socket function, socket no //
//         const struct sockaddr *servaddr : server socket address   //
//					    structure		     //
//         socket_t addrlen : size of structure servaddr             //
// Output : non negative descriptor : OK			     //
//           -1 : error 					     //
// Purpose : to set connection to server			     //
///////////////////////////////////////////////////////////////////////
// unsigned long int inet_addr(costt char *cp)			     //
// ================================================================= //
// Input : cp : Dotted decimal notation(ex 192.168.1.102)	     //
// Output : 32bit big endian binary data 			     //
//          -1 : input is invalid, INADDR_NONE			     //
// Purpose : dotted decimal form to binary data in network byte order//
///////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>	
#include<netinet/in.h>
#include<arpa/inet.h>	//to use inet_addr function
#define BUFFSIZE	1024
#define PORTNO		40000

int main()
{
	int socket_fd, len;//server socket file descriptor, size of data
	struct sockaddr_in server_addr;//server sockett address structure
	char haddr[] = "127.0.0.1";//IP adress in IPv4
	char input_url[BUFFSIZE];//input url
	char MissOrHit[BUFFSIZE];//miss or hit

	/////////////////make socket////////////////////////
	if((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)//make socket, IPv4, TCP type
	{
		printf("Can't create socket.\n");
		return -1;
	}
	/////////////////make socket address strucutre/////////////////////////
	bzero(input_url, sizeof(input_url));//initialize input url
	bzero((char*)&server_addr, sizeof(server_addr));//initialize server_addr
	server_addr.sin_family = AF_INET;//IPv4
	server_addr.sin_addr.s_addr = inet_addr(haddr);//127.0.0.1 -> 32bit binary data
	server_addr.sin_port = htons(PORTNO);//port number
	
	if(connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{//send connection request to server, and get socket about server into server_addr
		printf("Can't connect.\n");
		return -1;
	}

	while(1)//input url loop
	{
		printf("input url > ");
		scanf("%s", input_url);//input url
		if(write(socket_fd, input_url, strlen(input_url)+1) > 0)
		{//write input url to server
			if(!strcmp(input_url, "bye"))//if bye input
			{
				close(socket_fd);//close server socket
				return 0;//exit program
			}
			if((len = read(socket_fd, MissOrHit, sizeof(MissOrHit)))>0)//get Miss or hit from server
			{
				printf("%s\n", MissOrHit);
				//initialize each string
				bzero(input_url, sizeof(input_url));
				bzero(MissOrHit, sizeof(MissOrHit));
			}
		}
	}
	return 0;
}
