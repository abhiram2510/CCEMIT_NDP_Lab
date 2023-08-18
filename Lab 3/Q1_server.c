#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define myport 1234

int main(){
	int size,received,sent;
	int sockfd= socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_addr, c_addr;
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(myport);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(server_addr.sin_zero,'\0',sizeof(server_addr.sin_zero));
	bind(sockfd,(struct sockaddr*) &server_addr, sizeof(server_addr));
	//ready for listening
	listen(sockfd,1);
	printf("The server is listening.\n");
	
	size= sizeof(c_addr);
	int afd = accept(sockfd,(struct sockaddr*) &c_addr, &size);
	int buffer[50],buffer2[50];
	int pid = fork();
	while(1){
		if(pid>0){
			printf("PID: %d, PPID:%d\n",pid,getppid());
			printf("Message:");
			scanf("%s",buffer);
			sent =  send(afd,buffer,sizeof(buffer),0);
			if(sent == -1){
				printf("Message sending failed!");
				close(sockfd);
				close(afd);
				exit(0);
			}
		}
		else{
			received = recv(afd,buffer2,sizeof(buffer2),0);
			printf("PID: %d, PPID:%d\n",pid,getppid());
			if(received == -1){
				printf("Message recieving failed!");
				close(sockfd);
				close(afd);
				exit(0);
			}
			if(strcmp(buffer2,"BYE")==0){
				break;
			}
			printf("Child Message:");
			printf("%s\n",buffer2);
			
		}
	}
	close(afd);
	close(sockfd);

}
