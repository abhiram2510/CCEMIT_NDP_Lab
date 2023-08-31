#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "dns_socket"); // Set a unique socket file name

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    // Listen for incoming connections
    listen(server_socket, 5);

    while (1) {
        // Accept client connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Error accepting client connection");
            continue;
        }

        char query[100];
        // Receive DNS query from client using recv()

        // Simulate database lookup (using a text file)
        char response[100];
        FILE *database = fopen("database.txt", "r");
        while (fgets(response, sizeof(response), database)) {
            char name[100], ip[100];
            sscanf(response, "%s %s", name, ip);
            if (strcmp(query, name) == 0) {
                // Found a match in the database
                send(client_socket, ip, sizeof(ip), 0);
                break;
            }
        }
        fclose(database);

        // Send response (IP address or "Not found") back to client using send()

        // Close client socket
        close(client_socket);
    }

    close(server_socket);
    unlink("dns_socket"); // Clean up the socket file
    return 0;
}
