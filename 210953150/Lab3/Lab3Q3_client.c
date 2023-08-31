#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> // Include this header for inet_addr

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    server_addr.sin_port = htons(12345); // Server port number

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(1);
    }

    char message[256];
    printf("Enter an alphanumeric string: ");
    fgets(message, sizeof(message), stdin);
    message[strlen(message) - 1] = '\0'; // Remove newline

    send(client_socket, message, strlen(message), 0);

    char result[256];
    memset(result, 0, sizeof(result));
    recv(client_socket, result, sizeof(result), 0);

    printf("Received sorted result from server: %s\n", result);

    close(client_socket);

    return 0;
}
