// write, strstr, bzero, atoi, sprintf, strlen, exit, strcpy, strcat, memset
// malloc, realloc, free, calloc
// close, select, socket, accept, listen, send, recv, bind

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/select.h> //fd_set
// Your program must not contains #define preproc

int ids[6000];
int ids_count = 0, max_fds = 1 ;
fd_set readfds, writefds, current_fds;

char message[6000];

void client_joined() //do i need to pass anything?
{
    // FD_SET(); //add the new client to the set
    // sprintf(message, "server: client %d just arrived\n", ); //add the massege to the string to be sent to the clients, %d is the new client's id
    // send(); //send it to all of the current clients except for this new client. So we need a loop
    // ids_count++; //increment ids_count to prepare it for the next client
}

void new_message() //do i need to pass anything?yes, we need the client's id to avoid sending the message to him. We also need to get the message it wants to send to everyone
{
    // sprintf(message, "client %d: ...message...\n", ); //add the message to be sent & the client's id
    // send(); //send it to all of the current clients except for this new client. So we need a loop
}

void someone_left() //do i need to pass anything?yes, we need the client's id to be disconnected
{
    // sprintf(message, "server: client %d just left\n", ); //add the client's id
    // send(); //send it to all of the current clients that are connected except for this new client. So we need a loop
    // FD_CLR(); //remove the fd from list
    // close(); // i need to close fd
}

int main(int ac, char **argv) // This program will take as first argument the port to bind to
{
    if (ac != 2)
    {
        write (2, "Wrong number of arguments\n", 27);
        exit (1);
    }
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    FD_ZERO(&current_fds);

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		write(2, "Fatal error\n", 13); 
		exit(1); 
	}
    else {printf("Socket created\n");}
	bzero(&servaddr, sizeof(servaddr)); 
    FD_SET(sockfd, &current_fds); //should this take the original fd set?

    servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(8081); 

    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		write(2, "Fatal error\n", 13); 
		exit(1);  
	} 
	else {printf("Binding done\n");}
	if (listen(sockfd, SOMAXCONN) != 0) { //the max connections was set to = 10
		write(2, "Fatal error\n", 13); 
		exit(1); 
	}
    else {printf("Listening done\n");}

    while(1)
    {
        readfds = writefds = current_fds;
        if (select(max_fds, &readfds, &writefds, 0, 0) <= 0){
            write(2, "Fatal error\n", 13); 
		    exit(1); 
        }
        // if (accept(sockfd, (struct sockaddr *)&cli, &len) < 0) { 
        //     write(2, "Fatal error\n", 13); 
        //     exit(1);
        // } 
        // accept, recv,
    }
    // printf("finished\n");




}

// use "nc localhost port_num" to test the code