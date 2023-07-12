#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define PORT 9000

main( )
{
	int	c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int	len;

	int	n;
	char	rcvBuffer[BUFSIZ];

	s_socket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);

	if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
		printf("Can not Bind\n");
		return -1;
	}

	if(listen(s_socket, 5) == -1) {
		printf("listen Fail\n");
		return -1;
	}

	while(1) {
		len = sizeof(c_addr);
		c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);

		while((n = read(c_socket, rcvBuffer, sizeof(rcvBuffer))) != 0) {
				rcvBuffer[n] = '\0';
			printf("%s", rcvBuffer);
			write(c_socket, rcvBuffer, n);
		}
		close(c_socket);
	}
	close(s_socket);
}