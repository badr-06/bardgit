#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <arpa/inet.h>

#define PORT 8080

int main(){

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    int res = inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    if(res == 0){
        std::cerr << "src does not contain a character string representing a valid network address (for the specified address type)" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if(res == -1){
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    if(connect(fd, (struct sockaddr*) &addr, sizeof(addr)) == -1){
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    write(fd, "Hello\n", 6);

    close(fd);

    return 0;
}