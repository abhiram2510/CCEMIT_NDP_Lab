#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

int main() {
    int client_socket;
    struct sockaddr_un server_addr;
    
    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(1);
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "chat_socket");
    
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(1);
    }
    
    printf("Connected to server.\n");
    
    while (1) {
        char message[256];
        printf("Client: ");
        fgets(message, sizeof(message), stdin);
        message[strlen(message) - 1] = '\0'; // Remove newline
        
        send(client_socket, message, strlen(message), 0);
        
        memset(message, 0, sizeof(message));
        int bytes_received = recv(client_socket, message, sizeof(message), 0);
        if (bytes_received <= 0) {
            printf("Server disconnected.\n");
            break;
        }
        
        printf("Server: %s\n", message);
    }
    
    close(client_socket);
    
    return 0;
}
