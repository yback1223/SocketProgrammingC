#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> // inet_addr()
#include <stdlib.h>

#define PORT 9000
#define IPADDR "127.0.0.1"

char	buffer[BUFSIZ];

main( )
{
	int	c_socket;
	struct sockaddr_in c_addr;
	int	len;
	char	rcvBuffer[BUFSIZ];
	int	n;
	char	*temp;
	int	length = 0;


	// 1. 소켓 생성
	c_socket = socket(PF_INET, SOCK_STREAM, 0);

	// 2. 연결할 서버의 주소 설정
	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);

	// 3. 소켓을 서버에 연결, os에서 알아서 포트를 지정하여 서버에 연결 요청을 한다.
	if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr)) == -1) {
		printf("Can not connect\n");
		close(c_socket);
		return -1;
	}

	// 4. 서비스 요청과 처리, 서버로 전송
	scanf("%s", buffer);
	buffer[strlen(buffer)] = '\0';
	if((n = write(c_socket, buffer, strlen(buffer)+1)) < 0) {
		printf("write error\n");
		exit(-1);
	}

	// 5. 서버에서 온 데이터 읽기
	temp = rcvBuffer;
	while((n = read(c_socket, temp, 1)) > 0) {
		if(length == BUFSIZ) break;
		temp++; length++;
	}

	rcvBuffer[length] = '\0';
	printf("received Data : %s\n", rcvBuffer);

	// 6. 소켓 연결 종료
	close(c_socket);
}
