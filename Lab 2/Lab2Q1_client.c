#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define myport 1234

int main(){
int sockfd = socket(AF_INET,SOCK_STREAM,0);
if(sockfd == -1)
	{	printf("socket creation error");
		exit(0);
	}
	struct sockaddr_in c_addr;
	c_addr.sin_port = htons(myport);
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(c_addr.sin_zero, '\0', sizeof(c_addr.sin_zero));
	
	int size = sizeof(struct sockaddr);
	connect(sockfd, (struct sockaddr*) &c_addr, sizeof(c_addr));

	int buffer[10];
	char fname[10];
	while(1){
		printf("Enter the name of the file");
		scanf("%s",&fname);
		send(sockfd,fname,sizeof(fname),0);
		recv(sockfd,buffer,sizeof(buffer),0);
	}
}
