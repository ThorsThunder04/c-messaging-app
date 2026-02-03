//
// Created by snaug on 01/02/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <string.h>
#include "utils.h"

#define SERVER_PORT 16116
#define SERVER_IP argv[1]
#define BUFF_SIZE 1024
#define USERNAME_SIZE 16



int main(int argc, char **argv)
{
    int res = 0;
    char buff[BUFF_SIZE];

    if (argc != 2) {
        printf("Expected usage: %s <ip_address>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // username input
    char username[25] = {'\0'};
    do {

        printf("Enter a username (max length 16) : ");
        scanf("%s", username);

        if (strlen(username) > 16) {
            printf("Username too long. Try again !\n");
        } elif (strlen(username) == 0) {
            printf("You must enter a username. Try again !\n");
        }

    } while (strlen(username) == 0 || strlen(username) > 16)


    // creation of client's socket
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Error creating client's socket\n");
        exit(EXIT_FAILURE);
    }

    // definition of the server's IP
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));

    serv_addr.sin_family = PF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    if (inet_aton(SERVER_IP, &(serv_addr.sin_addr)) == 0) {
        pritnf("Error parsing IP, verify that it is in IPv4 format\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // connect socket to server
    res = connect(
        sockfd,
        (struct sockaddr*)&serv_addr,
        sizeof(struct sockaddr)
    );

    if (res == -1) {
        printf("Connection error!\n");        
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // check if server chatroom full
    res = myRect(sockfd, (void*)buff, sizeof(char), 0);
    if (res && buff[0] == 'r') {
        printf("Server Chatroom is full ! Try again later.\n");
        close(sockfd);
        exit(1);
    }

    

    // setup array to be used by seelct()
    fd_set fds[2] = {stdin, sockfd};
    int nfds = __max(fds[0], fds[1]);

    fd_set readfds[2];
    memcpy(readfds, fds, sizeof(fd_set));

    // send username
    buff[0] = 'u';
    buff[1] = '\0';
    strcpy(&(buff[1]), username);
    res = mySend(sockfd, (void*)buff, USERNAME_SIZE+2, 0);


    // Recieve and send messages loop





    return 0;
}