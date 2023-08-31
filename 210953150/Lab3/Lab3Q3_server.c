#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

void sort_numbers(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

void sort_characters(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (str[j] < str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(12345); // Port number

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

        pid_t child_pid = fork();
        if (child_pid == 0) { // Child process
            close(server_socket);

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            recv(client_socket, buffer, sizeof(buffer), 0);

            printf("Child Process - PID: %d, sorting numbers...\n", getpid());

            sort_numbers(buffer);
            send(client_socket, buffer, strlen(buffer), 0);
            
            printf("Child Process - PID: %d, sorted numbers sent\n", getpid());

            close(client_socket);
            exit(0);
        } else if (child_pid > 0) { // Parent process
            close(client_socket);

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            recv(client_socket, buffer, sizeof(buffer), 0);

            printf("Parent Process - PID: %d, sorting characters...\n", getpid());

            sort_characters(buffer);
            send(client_socket, buffer, strlen(buffer), 0);
            
            printf("Parent Process - PID: %d, sorted characters sent\n", getpid());
        } else {
            perror("fork");
        }
    }

    close(server_socket);

    return 0;
}
