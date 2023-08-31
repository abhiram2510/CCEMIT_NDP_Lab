#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
    int client_socket;
    struct sockaddr_un server_addr;

    client_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "chat_socket");

    char message[256];
    printf("Enter a string: ");
    fgets(message, sizeof(message), stdin);
    message[strlen(message) - 1] = '\0'; 

    sendto(client_socket, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Message sent to server.\n");

    close(client_socket);

    return 0;
}

