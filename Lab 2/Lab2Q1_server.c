#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define myport 1234
int main(){
int s, r, recb, sntb, x, ns, a = 0;
int size;
int sockfd = socket(AF_INET,SOCK_STREAM,0);
char buff[50];
if(sockfd == -1){
printf("\n Socket creation error");
exit(0);
}
printf("\n Socket Created!");
struct sockaddr_in server,client;

server.sin_family= AF_INET;
server.sin_port= htons(myport);
server.sin_addr.s_addr = htlon(INADDR_ANY);
r= bind(sockfd,(struct sockaddr*)&server, sizeof(server));
if(r == -1){
printf("\n Binding Error!");
exit(0);
}
printf("\n Socket Binded");

r=listen(sockfd,1);
if(r == -1){
close(s);
exit(0);
}
printf("\n Socket Listening!");

len = sizeof(client);
ns= accept(sockfd,(struct sockaddr*)&client, &len);
if(ns == -1){
close(s);
exit(0);
}
printf("\n Socket Accepting");

recb = recv(ns,buff,sizeof(buff),0)
if(recb == -1){
printf("\n Message Recieving Failed");
close(s);
close(ns);
exit(0);
}
printf("\n File Name recieved");
char fil[50];
if(access(buff, F_OK) != -1){
strcpy(fill,buff);
strcpy(buff,"File Exists');
}
else{
strcpy(buff,"File does not exist");
}

sntb =  send(ns, buff, sizeof(buff),0);
if(sntb == 0){
printf("Message Sending Failed!");
close(s);
close(ns);
exit(0);
}

if(strcmp(buff,"File does not exist") == 0){
close(s);
close(ns);
exit(0);
}


}
