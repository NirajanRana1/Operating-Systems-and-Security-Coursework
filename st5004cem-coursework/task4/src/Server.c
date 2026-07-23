#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int fd, c;
    struct sockaddr_in a = {AF_INET, htons(8080), INADDR_ANY}; // Setup port 8080
    char b[1024] = {0};

    // Create, bind, listen (with error check)
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 || bind(fd, (struct sockaddr*)&a, sizeof(a)) < 0 || listen(fd, 5) < 0) return 1;
    printf("Server running...\n");

    while (1) {
        if ((c = accept(fd, NULL, NULL)) < 0) continue; // Accept client

        if (fork() == 0) { // Clone process to handle client (concurrent)
            close(fd);
            read(c, b, 1024); // Read auth protocol

            // Security: check password
            if (strcmp(b, "AUTH:admin:123") != 0) { send(c, "FAIL", 4, 0); return 1; }
            send(c, "OK", 2, 0);

            // Chat protocol loop
            while (read(c, b, 1024) > 0) {
                if (b[0] == 'E') break; // EXIT protocol
                send(c, b, strlen(b), 0); // Echo MSG protocol back
            }
            return 0;
        }
        close(c);
    }
}
