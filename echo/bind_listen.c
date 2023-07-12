#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

main( )
{
	int s_socket;
	struct sockaddr_in s_addr;

	s_socket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 자신의 IP 주소로 변경
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(9000);

	if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
		printf("Can not Bind\n");
		return -1;
	}
	
	listen(s_socket, 0);

	while(1) {
		sleep(2);
	}

	close(s_socket);
}
