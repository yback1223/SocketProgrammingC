#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h> // inet_addr()

#define PORT 9000
#define IPADDR "127.0.0.1"

int main() {
	int c_socket;
	struct sockaddr_in c_addr;
	int len;
	int n;

	char rcvBuffer[BUFSIZ];

	// 1. 소켓 생성
	c_socket = socket(PF_INET, SOCK_STREAM, 0);

	// 2. 연결할 서버의 주소 설정
	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);

	// 3. 소켓을 서버에 연결, os에서 알아서 포트를 지정하여 서버에 연결 요청을 한다.
	if (connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr))== -1) {
		printf("Can't connect\n");
		close(c_socket);
		return -1;
	}

	// 4. 서비스 요청과 처리
	if ((n = read(c_socket, rcvBuffer, sizeof(rcvBuffer))) < 0) {
		return -1;
	}

	rcvBuffer[n] = '\0';
	printf("received Data: %s\n", rcvBuffer);

	// 5. 소켓 연결 종료
	close(c_socket);
}