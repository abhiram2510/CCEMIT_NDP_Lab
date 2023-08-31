#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

void handle_client(int client_socket) {
    char buffer[256];
    
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            printf("Client disconnected.\n");
            break;
        }
        
        printf("Client: %s\n", buffer);
        
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strlen(buffer) - 1] = '\0'; // Remove newline
        send(client_socket, buffer, strlen(buffer), 0);
    }
    
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(1);
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "chat_socket");
    
    unlink("chat_socket"); // Remove the socket file if it already exists
    
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }
    
    if (listen(server_socket, 5) == -1) {
        perror("listen");
        exit(1);
    }
    
    printf("Server is listening...\n");
    
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }
        
        printf("Client connected.\n");
        
        pid_t child_pid = fork();
        if (child_pid == 0) { // Child process
            printf("Child Process - PID: %d, PPID: %d\n", getpid(), getppid());
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        } else if (child_pid > 0) { // Parent process
            printf("Parent Process - PID: %d, Child PID: %d\n", getpid(), child_pid);
            close(client_socket);
        } else {
            perror("fork");
        }
    }
    
    close(server_socket);
    unlink("chat_socket");
    
    return 0;
}
