#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

void permute(char *str, int start, int end) {
    if (start == end) {
        printf("%s\n", str);
        return;
    }

    for (int i = start; i <= end; i++) {

        char temp = str[start];
        str[start] = str[i];
        str[i] = temp;


        permute(str, start + 1, end);

        
        temp = str[start];
        str[start] = str[i];
        str[i] = temp;
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "chat_socket");

    unlink("chat_socket"); 

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    printf("Server is listening...\n");

    while (1) {
        char buffer[256];
        memset(buffer, 0, sizeof(buffer));

        recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_len);
        printf("Received from client: %s\n", buffer);

        printf("Permutations:\n");
        permute(buffer, 0, strlen(buffer) - 1);
    }

    close(server_socket);
    unlink("chat_socket");

    return 0;
}
