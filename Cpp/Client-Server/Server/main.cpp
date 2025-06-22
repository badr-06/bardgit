#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>


#define PORT 8080
#define MAX_CLIENTS 10

int main(){

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in addres = {};
    addres.sin_family = AF_INET;
    addres.sin_addr.s_addr = INADDR_ANY;
    addres.sin_port = htons(PORT);
    if(bind(server_fd, (struct sockaddr*) &addres, sizeof(addres)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    listen(server_fd, MAX_CLIENTS);
    std::cout << "[+] Server listening on port " << PORT << "...\n";

    socklen_t addrlen = sizeof(addres);
    int fd = accept(server_fd, (struct sockaddr*) &addres, &addrlen);
    char buf[1024];
    int bytes_read = read(fd, &buf, sizeof(buf));
    if(bytes_read == -1){
        perror("read failed");
        exit(EXIT_FAILURE);
    }
    std::string buffer(buf, bytes_read);
    write(STDOUT_FILENO, buf, bytes_read);

    sleep(3);

    close(fd);
    close(server_fd);
    return 0;
}