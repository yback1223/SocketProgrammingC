#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#define PORT 9000

char	err_1[ ]="Directory Error";
char buffer[BUFSIZ] = "hello, world";
char	rBuffer[BUFSIZ];

int main() {
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len, length;
	int n, i;
	char *temp;
	DIR *dp;
	struct dirent *dir;

	// 1. 소켓 생성
	s_socket = socket(PF_INET, SOCK_STREAM, 0);
	
	// 2. 연결 요청을 수신할 주소 설정
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);

	// 3. 소켓을 포트에 연결
	if (bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
		printf("Can't bind\n");
		return -1;
	}

	// 4. 커널에 개통 요청
	if (listen(s_socket, 5) == -1) {
		printf("listen fail\n");
		return -1;
	}

	while(1) {
		len = sizeof(c_addr);

		// 5. 클라이언트 연결 요청 대기 및 수신
		c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);

		// 6. 클라이언트 요청 서비스 제공
		length = 0;
		temp = rBuffer;
		while((n = read(c_socket, temp, 1)) > 0) {
			if(*temp == '\r') continue;
			if(*temp == '\n') break;
			if(*temp == '\0') break;
			if(length == BUFSIZ) break;
			temp++; length++;
		}

		rBuffer[length] = '\0';

		if(!strcmp(rBuffer, "print") ) {
			n = strlen(buffer);
			write(c_socket, buffer, n);
		} else if (!strcmp(rBuffer, "ls") ) {

			if((dp = opendir(".")) == NULL) {
				write(c_socket, err_1, strlen(err_1));
			} else {
				while((dir = readdir(dp)) != NULL) {
					if(dir->d_ino == 0) continue;
					write(c_socket, dir->d_name, strlen(dir->d_name));
					write(c_socket, " ", 1);
				}
				closedir(dp);
			}
		}
		close(c_socket);
	}
	close(s_socket);
}