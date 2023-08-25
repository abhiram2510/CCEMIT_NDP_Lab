#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define myport 1234
struct student{
	char regno[10];
	char name[10];
	char subject[10][10];
	char marks[10][10];
	char semester[10];
	char address[10];
	char department[10];
};
struct 
int main()
{
	//create assign bind listen accept operate reply
	int size;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);	//socket creation
	struct sockaddr_in	server_addr, c_addr;	
	
	//feeding values into the socket address structure
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(myport);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset( server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero) );
	
	bind( sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr) );
	
	//ready for listening
	listen(sockfd, 10);
	printf("The server is ready for listening.\n");
	size = sizeof(struct sockaddr);
	
	int afd = accept(sockfd, (struct sockaddr *) & c_addr, &size);
	
	//loading values into the structure.
	struct student student1[2];
	struct subject subject1[4];
	strcpy(student1[0].regno,"210953150");
	strcpy(student1[1].regno,"210953154");
	strcpy(student[0].name,"Abhiram");
	strcpy(student[1].name,"Sahith");
	strcpy(student[0].marks,"10");
	strcpy(student[1].marks,"100");
	strcpy(student[0].semester,"2");
	strcpy(student[1].semester,"3");
	strcpy(student[0].address,"Bangalore");
	strcpy(student[1].address,"Hyderabad");
	strcpy(student[0].department,"ICT");
	strcpy(student[1].department,"CSE");
	strcpy(student[0].subject[0],"Software Dev");
	strcpy(student[0].subject[1],"NPACN");
	strcpy(student[1].subject[0],"Information Security");
	strcpy(student[1].subject[1],"EOM");
	strcpy(student[0].marks[0],"28");
	strcpy(student[0].marks[1],"27");
	strcpy(student[1].marks[0],"30");
	strcpy(student[1].marks[1],"30");
