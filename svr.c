///////////////////////////////////////////////////////////////////////
// File Name		: svr.c			             	     //
// Date			: 2021/4/28			             //
// Os 			: Ubuntu 16.04 LTS 64bits	   	     //
// Author 		: Jeong Eal Young		             //
// Student ID		: 2016722033				     //
// ----------------------------------------------------------------- //
// Title : System Programing Assignment #2-1			     //
// Description : This assignment is about implementing server-client //
// and socket programing. In this code, A programming that implements//
// a server that handles multiple clients has been written. 	     //
// When client send connect require, Server makes sub process and    //
// waits for a client's communication connection. When client sends  //
// input url, sub process makes cache directory, new directories and //
// files by hashed url in cache directory, determines hit or miss    //
// like assignment#1-2.						     // 
///////////////////////////////////////////////////////////////////////
// char *sha1_hash(char *input_url, char *hashed_url)                //
// ================================================================= //
// Input : char *input_url : Input original  URL by user	     //
//         char *hashed_url : hashed URL converted to hexademica     //
// Output : hashed_url : hashed URL converted to hexademical with    //
//                       SHA1, strcpy function                       //
// Purpose : convert input url to hash url and make it char * type   //
///////////////////////////////////////////////////////////////////////
// char *getHomeDir(char* home)					     //
// ================================================================= //
// Input : char* home : array that hold path of home directory	     //
// Output : char* home : array that hold path of home directory      //
// Purpose : get path of home directory	and make cache in home       //
//           directory						     //
///////////////////////////////////////////////////////////////////////
// int mkdir(const char *pathname, mode_t mode)			     //
// ================================================================= //
// Input : const char *pathname : path and name of directory	     //
//         mode_t mode : access permission of directory              //
// Output : -l : make directory error				     //
//          or : make directory success                              //
// Purpose : make directory where user wants			     //
///////////////////////////////////////////////////////////////////////
// DIR * opendir(const char * pathname)				     //
// ================================================================= //
// Input : const char * path : path and name of directory            //
//                             to open 				     //
// Output : DIR type pointer : indicates opened directory            //
// Purpose : open directory to get information			     //
//           NULL : on error		  			     //
///////////////////////////////////////////////////////////////////////
// struct dirent *readdir(DIR *dp)                                   //
// ================================================================= //
// Input : DIR *dp : directory pointer to read                       //
// Output : struct dirent : pointer represent next directory         //
//          NULL : on error or end of the directory		     //
// Purpose : search directories in directory  			     //
///////////////////////////////////////////////////////////////////////
// void closedir(DIR *dp)					     //
// ================================================================= //
// Input : DIR *dp : directory pointer to close 		     //
// Purpose : close directory 					     //
///////////////////////////////////////////////////////////////////////
// int open(const char *FILENAME, int FLAGS[, mode_t MODE])	     //
// ================================================================= //
// Input : const char *FILENAME : name of file including path        //
//        int FLAGS : option about file open e.g. O_RDONLY, O_WRONLY //
//                    O_CREAT, O_TRUNC, O_EXCL                       //
//         [mode_t MODE] : file permission when using O_CREAT option //
///Output : int 0< : file descriptor				     //
//              -1 : failure                                         //
// Purpose : create or open file                                     //
///////////////////////////////////////////////////////////////////////
// ssize_t write(int fd, const void *buf, size_t n)                  //
// ================================================================= //
// Input : int fd : file descriptor                                  //
//         void *buf : buffer with contents to be written to the file//
//         size_t n : number of bytes to write 		 	     //
// Output : ssize_t : number of bytes written                        //
//               -1 : failure					     //
// Purpose : write information in txt file or sending data to file   //
///////////////////////////////////////////////////////////////////////
// ssize_t read(int filedes, void *buf, size_t nbytes)		     //
// ================================================================= //
// Input : int filedes : file descriptor to receive data	     //
// 	   void *buf : buffer to save received data		     //
// 	   size_t nbytes : maximum of bytes to receive	   	     //
// Output : number of bytes to receive				     //
// Purpose : read information from another process		     //
///////////////////////////////////////////////////////////////////////
// time_t time(const time_t *timer)                                  //
// ================================================================= //
// Input : const time_t *timer : pointer to storage location         //
//                             corresponding to time                 //
// Output : the number of seconds that have elapsed since midnight on//
//          January 1, 1970                                          //
//         -1 : failure                                              //
// Purpose : to get present time                                     //
///////////////////////////////////////////////////////////////////////
// struct tm * localtime(const time_t * sourceTime)		     //
// ================================================================= //
// Input : const time_t *sourceTime : pointer to saved time          //
// Output : struct tm : structure about time                         //
// Purpose : to get time structure                                   //
///////////////////////////////////////////////////////////////////////
// pid_t fork(void)						     //
// ================================================================= //
// Output : pid_t Child process 0 : return 0 in child process        //
//              parent process : process ID of the new child         //
//              Error : -1  					     //
// Purpose : make new childe process that has copy of the parent's   //
//           data and stack 					     //
///////////////////////////////////////////////////////////////////////
// pid_t wait(int *statloc)                                          //
// ================================================================= //
// Input : int *statloc : has status of ended program		     //
// Output : process ID : process ID to wait                          //
//                  -1 : error                                       //
// Purpose : wait till child process ends			     //
///////////////////////////////////////////////////////////////////////
// int bind(int sockfd, const struct sockaddr *myaddr, socklen_t len)//
// ================================================================= //
// Input : int sockfd : return of calling socket function, socket no //
// 	   const struct sockaddr : server's onw socket address	     //
//                                 structure pointer		     //
//         socklen_t addrlen : size of myaddr structure		     //
// Output : 0 : OK						     //
//         -1 : error 						     //
// Purpose : binding socket and sockaddr_in structure		     //
//           assign ip, port num in structure to use generated socket//
///////////////////////////////////////////////////////////////////////
// int listen(int sockfd, int backlog)				     //
// ================================================================= //
// Input : int sockfd : return of calling socket function, socket no //
//         int backlog : the length of waiting queue	             //
// Output : 0 : OK						     //
//         -1 : error 						     //
// Purpose : When a connection request comes from client, it is put  //
//           in the waiting queue				     //
///////////////////////////////////////////////////////////////////////
// int accept(int sockfd, struct sockaddr *cliaddr, socklen_t *len)  //
// ================================================================= //
// Input : int sockfd : return of calling socket function, socket no //
//         struct sockaddr *cliaddr : socket structure of the client //
//				      requesting the connection      //
//         socklen_t *addrlen : size of cliaddr structure	     //
// Output : nonnegative descriptor : OK				     //
//          -1 : error					   	     //
// Purpose : Server accept client's connection			     //
///////////////////////////////////////////////////////////////////////
// int close(int filedes)			 		     //
// ================================================================= //
// Input : int filedes : file descriptor 			     //
// Output : 0 : OK						     //
//         -1 : error						     //
// Purpose : close file descriptor 				     //
///////////////////////////////////////////////////////////////////////
// unsigned long int htonl(unsigned long int hostlong)	    	     //
// ================================================================= //
// Input : unsigned long int hostlong : IP address 	    	     //
// Output : IP address to network byte order			     //
// Purpose : Unify network byte order 			             //
///////////////////////////////////////////////////////////////////////
// unsigned short int htons(unsigned short int hostshort)	     //
// ================================================================= //
// Input : unsigned short int hostshort : port number 		     //
// Output : port number to network byte order			     //
// Purpose : Unify network byte order 				     //
/////////////////////////////////////////////////////////////////////// 

#include<stdio.h>		//I/O function (printf, scanf, sprintf)
#include<string.h>		//string function(strcpy, strcat)
#include<sys/types.h>		//uid_t, pid_t structure
#include<sys/wait.h>		//wait function
#include<sys/socket.h>		//sockadder_in structure, socket, accept, bind function
#include<sys/stat.h>		//mkdir function
#include<openssl/sha.h>		//SHA1 function
#include<dirent.h>		//Directory structure and function
#include<pwd.h>			//getpwuid function
#include<fcntl.h>		//creat function
#include<netinet/in.h> 		//htonl, htons function
#include<unistd.h>		//read, write, close function
#include<signal.h>		//error handling
#include<stdlib.h>		//exit function
#include<time.h>		//time function and structure
#include<errno.h>			//use erron variable
#define BUFFSIZE 1024
#define PORTNO	40000

char* sha1_hash(char* input_url, char* hashed_url)// make hashed url from input url
{
	unsigned char hashed_160bits[20];
	char hashed_hex[41];
	int i;
	
	SHA1(input_url, strlen(input_url), hashed_160bits);
	for(i=0;i<sizeof(hashed_160bits);i++)
		sprintf(hashed_hex + i * 2, "%02x", hashed_160bits[i]);
	strcpy(hashed_url, hashed_hex);
	return hashed_url;
}
char* getHomeDir(char* home)//get Home directory path
{
	struct passwd* usr_info = getpwuid(getuid());
	strcpy(home, usr_info->pw_dir);
	return home;
}


int main()
{
	////////////////for socket variable/////////////////////////////////////
	struct sockaddr_in server_addr, client_addr;//server socket, client socket
	int socket_fd, client_fd;//server socket file descriptor, client socket file descriptor 
	int len, len_out;
	
	pid_t pid;
	time_t now;
	struct tm* ltp;
	///////////////for Assignment1-2 variable//////////////////////////////
	char input_url[1024];
	char hashed_url[1024];
	char cache_path[256] = {0};	//cache directory path
	char logfile_path[256] = {0};	// logfile directory path
	char logfiletxt_path[256] = {0}; // logfile.txt file path
	char dir_path[256] = {0}; 	//directory(in cache) path
	char dir_name[256] = {0};	//directory(in cache) name
	char file_path[256] = {0};	//file(in directory) path
	char com_dir_path[256] = {0};	//to compare input hashed url, directory name
	char com_url[256] = {0};	//hashed url in cache directory
	char hit1_str[256] = {0};	//logfile hit hashed url
	char hit2_str[256] = {0};	//logfile hit input url
	char miss_str[256] = {0};	//logfile miss input url
	char time_str[256] = {0};	//logfile time string
	char terminated_str[256] = {0};	//logfile terminated string
	
	int mResult;	//result of making directory or file
	int log_write;	//file descriptor of logflie.txt
	int i; 		//index for loop
	int hit_flag=0;	//hit or miss flag, 1 = hit, 0 = miss 
	
	int process_start_flag = 0; 	//process start flag
	long int process_start_time = 0;//time when process start

	int hit_c = 0;	//hit count
	int miss_c = 0; //miss count

	int statloc;//for wait function
	DIR *pDir;	//to check directory is hit or miss
	DIR* ppDir;	//to check file hit or miss
	struct dirent* pFile;	//search subdirectories in pDir;
	struct dirent* ppFile;	//search subdirectories in ppDir;

	
	umask(0);//give all permission to everyone
	
	/////////////////make socket////////////////////////
	if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)//IPv4, TCP type
	{
		printf("Server: Can't open stream socket.");//print error
		return 0;//end program
	}

	/////////////////binding socket/////////////////////////
	bzero((char*)&server_addr, sizeof(server_addr));//initialize server_addr
	server_addr.sin_family = AF_INET;//IPv4 internet protocol system
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//IP address
	server_addr.sin_port = htons(PORTNO);//port number
	
	//assign socket address into socket file descriptor = binding
	if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("Server: Can't bind local address.\n");//print error
		close(socket_fd);
		return 0;
	}
	/////////////////end of binding socket////////////////

	listen(socket_fd, 5);//manage the waiting queue for client connection 
	while (1)
	{
		bzero((char*)&client_addr, sizeof(client_addr));//initialize client_addr
		len = sizeof(client_addr);//get size of client_addr to use accept function

		//accept client's connection, assign client socket address into client socket file descriptor
		client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &len);
		if (client_fd < 0)
		{
			printf("Server: accept failed.\n");//print error
			return 0;
		}
		
		printf("[%d:%d] client was connected. \n", client_addr.sin_addr.s_addr, client_addr.sin_port);//print connected message
		
		
		pid = fork();//make sub process to do Assignment 1-2
		if(pid==-1)//if fork error
		{
			close(client_fd);//close client socket
			close(socket_fd);//close server socket
			return 0;
		}
		if(pid==0)//sub process does Assignment1-2
		{
			process_start_time = time(&now);//start time
			strcat(getHomeDir(cache_path), "/cache");	//make cache directory path
			strcat(getHomeDir(logfile_path), "/logfile");	//make logfile directory path
			mResult = mkdir(cache_path, 0777);	//make cache directory
			if(mResult == -1)//two case, directory already exist or make directory error
			{
				if(errno == ENOENT)
				{
					printf("make directory error\n");//make directory error
					close(socket_fd);
					close(client_fd);
					return 0;
				}
			}
			mResult = mkdir(logfile_path, 0777);	//make logfile directory
			if(mResult == -1)//two case, directory already exist or make directory error
			{
				if(errno == ENOENT)
				{
					printf("make directory error\n");//make directory error
					close(socket_fd);
					close(client_fd);
					return 0;
				}
			}
			//make logfile.txt path
			strcpy(logfiletxt_path, logfile_path);
			strcat(logfiletxt_path, "/logfile.txt");
			strcpy(dir_path, cache_path);		//get directory path in cache directory
			
			hit_c = 0;
			miss_c = 0;
			log_write = open(logfiletxt_path, O_CREAT | O_APPEND | O_WRONLY, 0777);//open logfile.txt
			if(log_write == -1)//make logfile.txt error
			{
				printf("make logfile.txt error\n");
				close(socket_fd);
				close(client_fd);
				return 0;
			}
			while(1)//get url from client and determine hit or miss
			{			
				hit_flag = 0;
				len_out = read(client_fd, input_url, 1024);//get input url from client
				if(!strncmp(input_url, "bye" ,3))//if bye input
				{
					log_write = open(logfiletxt_path, O_CREAT | O_WRONLY | O_APPEND, 0777);//open logfile.txt
					sprintf(terminated_str, "[Terminated] ServerPID : %d | run time : %ld sec. #request hit : %d, miss : %d\n", getpid(), time(&now)-process_start_time, hit_c, miss_c);//get time string
					write(log_write, terminated_str, strlen(terminated_str));//write time string
					for(i=0;i<strlen(terminated_str);i++) terminated_str[i] = 0;//initialize time string
					close(log_write);//close logfile.txt
					printf("[%d:%d] client was disconnected.\n", client_addr.sin_addr.s_addr, client_addr.sin_port);//print disconnect			
					break;//escape loop
				}
				time(&now);//get present time
				ltp = localtime(&now);//make local time from present time
				sprintf(time_str, " - [%d/%02d/%02d, %02d:%02d:%02d]", ltp->tm_year + 1900, ltp->tm_mon + 1, ltp->tm_mday, ltp->tm_hour, ltp->tm_min, ltp->tm_sec);//make time string
				sha1_hash(input_url, hashed_url);//make hashed url from input url
					
				pDir = opendir(cache_path);//open cache directory
				strncpy(dir_name, hashed_url, 3);//make directory name from hashed url
				
				for(pFile = readdir(pDir); pFile; pFile = readdir(pDir))
				{//search cache directory
					if(!strcmp(pFile->d_name, dir_name))//if dir_name is in cache
					{
						strcpy(com_dir_path, cache_path);
						strcat(com_dir_path, "/");
						strcat(com_dir_path, pFile->d_name);//make directory path to search this directory
						ppDir = opendir(com_dir_path);//open directory 
						for(ppFile = readdir(ppDir); ppFile; ppFile = readdir(ppDir))
						{//search directory
							if(!strcmp(ppFile->d_name, &hashed_url[3]))
							{//if there is same named file
								hit_flag = 1;//hit flag on
								break;//escape loop
							}
						}
						closedir(ppDir);//close directory
						for(i=0; i<strlen(com_dir_path); i++) //initialize directory path
							com_dir_path[i] = 0;
					}
					if(hit_flag) break;//if hit flag on, escape loop
				}
				closedir(pDir);//close cache directory
				if(hit_flag)//when input url is hit
				{//make hit log string and write in logfile.txt
					log_write = open(logfiletxt_path, O_CREAT | O_APPEND | O_WRONLY, 0777);
					sprintf(hit1_str, "[HIT] ServerPID : %d | %s/%s%s\n", getpid(), dir_name, &hashed_url[3], time_str);
					write(log_write, hit1_str, strlen(hit1_str));
					sprintf(hit2_str, "[HIT]%s\n", input_url);
					write(log_write, hit2_str, strlen(hit2_str));
					//initialize each string
					for(i=0;i<3;i++) dir_name[i] = 0;
					for(i=0;i<strlen(hit1_str);i++) hit1_str[i] = 0;
					for(i=0;i<strlen(hit2_str);i++) hit2_str[i] = 0;
					close(log_write);//close logfile.txt
					write(client_fd, "HIT", 4);//send HIT to client
					hit_c ++;//hit count ++
					for(i=0;i<strlen(input_url);i++) input_url[i] = 0;//initialize input url
					continue;//continue loop
				}
				else//input url is miss
				{//make miss log and write in logfile.txt
					log_write = open(logfiletxt_path, O_CREAT | O_APPEND | O_WRONLY, 0777);
					sprintf(miss_str, "[MISS] ServerPID : %d | %s%s\n", getpid(), input_url, time_str);
					write(log_write, miss_str, strlen(miss_str));
					//initialize miss string
					for(i=0;i<strlen(miss_str);i++) miss_str[i] = 0;
					close(log_write);//close logfile.txt
					write(client_fd, "MISS", 5);//sent MISS to client
					miss_c ++;//miss count ++
				}
				//get directory path and make it in cache directory
				strcat(dir_path, "/");
				strcat(dir_path, dir_name);
				mResult = mkdir(dir_path, 0777);
				if(mResult == -1) printf("make directory error\n");
				//get file path and make it in directory
				strcpy(file_path, dir_path);
				strcat(file_path, "/");
				strcat(file_path, &hashed_url[3]);
				mResult = creat(file_path, 0777);
				if(mResult == -1) printf("make file error\n");
				for(i=0;i<strlen(dir_path);i++) dir_path[i] = 0;//initialize directory path
				strcpy(dir_path, cache_path);//input cache directory path into directory path again
				//initialize each string
				for(i=0;i<strlen(dir_name);i++) dir_name[i] = 0;
				for(i=0;i<strlen(file_path);i++) file_path[i] = 0;
				for(i=0;i<strlen(input_url);i++) input_url[i] = 0;
			}
		}	
		close(client_fd);//close client socket
	}
	close(socket_fd);//close server socket
}
