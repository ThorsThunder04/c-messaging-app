#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "utils.h"

/**
 * @brief Wrapper for send() that handles failure by closing the file descriptor and displaying error
 * 
 * @param fd int: socket file descriptor
 * @param buff void*: buffer with data to send
 * @param size int: number of bytes from buffer to send
 * @param flags int: flags for send()
 * @return int number of bytes sent
 */
int myRecv(int fd, void* buff, int size, int flags) {
    
    int res = recv(fd, (void*)buff, size, flags);
    if (res == -1) {
        printf("Error recieving message\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    return res;
}

/**
 * @brief Wrapper for recv() that handles failure by closing the file descriptor and displaying error
 * 
 * @param fd int: socket file descriptor
 * @param buff void*: buffer to store recieved data
 * @param size int: number of bytes to read then write to buffer
 * @param flags int: flags for recv()
 * @return int number of bytes recieved | 0 if size=0 OR if peer socket closed
 */
int mySend(int fd, void* buff, int size, int flags) {

    int res = send(fd, (void*)buff, size, flags);
    if (res == -1) {
        printf("Error sending message\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    return res;
}