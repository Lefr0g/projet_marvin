#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define CRLF	 "\r\n"
#define PORT	 1977

#define BUF_SIZE_SOCKET 1024

int		init_connection(const char *);
void	end_connection(int);
int		read_server(SOCKET, char *);
void	write_server(SOCKET, const char *);
char	*ft_itoa(int);
#endif
