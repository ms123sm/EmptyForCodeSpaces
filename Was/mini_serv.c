#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/select.h>

// Your program must not contains #define preproc

fd_set readfds, writefds, tmpfds;
int max_fds = 1; // remember i started from 1 and not from 0
char buffer[4097];
int ids[1024], count = 0;

int main(int ac, char **argv)
{
    if (ac != 2)
    {
        write(2, "Wrong number of arguments\nm", 27);
        exit(1);
    }

	FD_ZERO(&readfds);
    FD_ZERO(&writefds);

    // Add file descriptors to fd_set
    // FD_SET(STDIN_FILENO, &readfds);  // FD_SET(0, &readfds); - stdin
    // FD_SET(STDOUT_FILENO, &writefds); // FD_SET(1, &writefds); - stdout
///////////////////////////////////////////////////////////////////////////////// socket

    int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		write(2, "Fatal error1\n", 13);
		exit(1); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 
	FD_SET(sockfd, &readfds);
	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1]));  //replaces 8081 with argcv[1]

///////////////////////////////////////////////////////////////////////////////// bind

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		write(2, "Fatal error2\n", 13);
		exit(1); 
	} 
	else
		printf("Socket successfully binded..\n");

///////////////////////////////////////////////////////////////////////////////// listen

	if (listen(sockfd, 10) != 0) { //you could change 10 to the max e.g. 180
		write(2, "Fatal error3\n", 13);
		exit(1); 
	}
	len = sizeof(cli);

///////////////////////////////////////////////////////////////////////////////// Almost all copy/paste until here. But change argv[1] && somaxconn size (socket max connections)

///////////////////////////////////////////////////////////////////////////////// accept
	// connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	// if (connfd < 0) { 
    //     write(2, "Fatal error\n", 12);
    //     exit(1); 
    // } 
    // else
    //     printf("server acccept the client...\n");
/////////////////////////////////////////////////////////////////////////////////

    while(1)
    {
		tmpfds = writefds = readfds;
		// FD_SET(sockfd, &readfds);
		if (select(max_fds, &tmpfds, &writefds, NULL, NULL) < 0)
		{
			write(2, "Fatal error4\n", 13);
			exit(1); 
		}
		// exit(0);
		printf("Succesful Select\n");
		for(int fd = 0; fd < max_fds; fd++)
		{
			if (fd == sockfd)
			{
				len = sizeof(cli);
				connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (connfd >= 0)
				{
					write(2, "NEW CONNECTION\n", 15);
					// printf("NEW CONNECTION\n");
					max_fds++;
					break ; 
				}
			}
			else
			{
				int read_size = recv(fd, &buffer, 4096, 0);
				if (read_size <= 0)
				{
					write(1, "Someone left\n", 13);
					// printf("Someone left\n");
					break ;
				}
				buffer[read_size] = '\0';
			}
		}

        break;
    }
// 1. socket //done
// 2. bind //done
// 3. listen //done
// 4. select //almost done, i just need to use it and work on max_fds
// 5. accept //alomst done, i need to use it
// ...
// 6. recv
// 7. send
// 8. close
}