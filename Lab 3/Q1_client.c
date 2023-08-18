#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define myport 1234

int main(){
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("socket creation error");
		exit(0);
	}
	struct sockaddr_in c_addr;
	c_addr.sin_port =  htons(myport);
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(c_addr.sin_zero,'\0',sizeof(c_addr.sin_zero));
	
	int size = sizeof(struct sockaddr);
	int c =	connect(sockfd,(struct sockaddr*)&c_addr,sizeof(c_addr));
	if(c == -1){
		printf("not connected");
	}
	else{
		printf("Connected!");
	}
	
	int buffer[50],buffer2[50];
	int pid,received,sent;
	pid = fork();
	while(1){
		if(pid>0){
			printf("PID: %d, PPID: %d\n", pid, getppid());
			received = recv(sockfd,buffer,sizeof(buffer),0);
			if(received == -1){
				printf("Message receiving failed");
				close(sockfd);
				exit(0);
			}
			if(strcmp(buffer,"BYE")==0){
				break;
			}
			printf("Message Received:");
			printf("%s\n",buffer);
		}
		else{
			printf("PID: %d, PPID: %d\n", pid, getppid());
			printf("Please enter the message to be sent from child process:");
			scanf("%s",buffer2);
			sent = send(sockfd,buffer2,sizeof(buffer2),0);
			if(sent == -1){
				close(sockfd);
				printf("Could not send message");
				exit(0);
			}
		}
	}
	close(sockfd);
}
