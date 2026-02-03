#ifndef UTILS_H
#define UTILS_H


/**
 * @brief Wrapper for send() that handles failure by closing the file descriptor and displaying error
 * 
 * @param fd int: socket file descriptor
 * @param buff void*: buffer with data to send
 * @param size int: number of bytes from buffer to send
 * @param flags int: flags for send()
 * @return int number of bytes sent
 */
int myRecv(int fd, void* buff, int size, int flags);

/**
 * @brief Wrapper for recv() that handles failure by closing the file descriptor and displaying error
 * 
 * @param fd int: socket file descriptor
 * @param buff void*: buffer to store recieved data
 * @param size int: number of bytes to read then write to buffer
 * @param flags int: flags for recv()
 * @return int number of bytes recieved | 0 if size=0 OR if peer socket closed
 */
int mySend(int fd, void* buff, int size, int flags); 

#endif