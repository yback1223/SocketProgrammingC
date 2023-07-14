# README

## helloWorldServer.c

`listen(s_socket, 5)`

- listen() 함수는 커널에 소켓 개통을 요청한다.

`c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);`

- accept() 함수는 blocking 함수이다.
  - 요청이 올 때까지 기다리고 있는다.
- s_socket은 듣기 전용 소켓(listen socket)이고, accept() 함수의 반환 값인 c_socket은 연결 전용 소켓(connection socket)이다.

`write(c_socket, buffer, n);`

- c_socket으로 buffer의 내용을 n의 크기만큼 전송한다.

## helloWorldClient.c

`connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr))`

- client의 소켓으로 서버에 연결 요청을 한다.

`read(c_socket, rcvBuffer, sizeof(rcvBuffer))`

- c_socket으로 부터 데이터를 읽는다.

## socketPair.c

`result = socketpair(PF_LOCAL, SOCK_STREAM, 0, sd);`

- socket을 두 개 생성하고, 심지어 두 소켓을 연결까지 해준다.
