//
// Created by snaug on 01/02/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "utils.h"

#define PORT 16116
#define BUFF_SIZE 1024
#define USERNAME_SIZE 16
#define PEER_COUNT 255
#define BACKLOG 10


int main(int argc, char* argv[]) {


    // creating server socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error creating server socket: ");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully !\n");


    // defining server's address
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind address to socket
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) == -1) {
        perror("Error binding socket :");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int sockets[PEER_COUNT+1] = {0};
    sockets[0] = sockfd;

    return 0;
}