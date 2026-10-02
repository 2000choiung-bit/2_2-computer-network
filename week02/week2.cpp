#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define SERVERPORT 9000 // 서버가 손님을 기다릴 포트 번호
#define BUFSIZE    512  // 한 번에 읽어올 데이터 버퍼 크기

// 에러 발생 시 메시지 출력 후 프로그램 종료
void err_quit(char *msg)
{
	printf("[%s]", msg);
	exit(1);
}

// 에러 발생 시 메시지만 출력하고 계속 진행
void err_display(char *msg)
{
	printf("[%s]", msg);
}

// TCP 서버의 메인 로직이 실행될 쓰레드 함수
DWORD WINAPI TCPServer4(LPVOID arg)
{
	int retval;

	// 1. socket() : 클라이언트 접속 요청을 받을 '듣기 소켓(Listen Socket)' 생성
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == INVALID_SOCKET) err_quit("socket()");

	// 2. bind() : 소켓에 IP 주소와 포트 번호(9000)를 바인딩(할당)
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // 내 PC의 모든 IP 주소로부터의 접속 허용
	serveraddr.sin_port = htons(SERVERPORT);        // 9000번 포트 연결
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if(retval == SOCKET_ERROR) err_quit("bind()");

	// 3. listen() : 클라이언트의 접속을 기다리는 대기 상태로 전환
	retval = listen(listen_sock, SOMAXCONN);
	if(retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수들
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];

	// 클라이언트 접속 수락 및 통신 반복문
	while(1){
		// 4. accept() : 클라이언트의 연결 요청을 수락하고, '전용 통신 소켓' 생성
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if(client_sock == INVALID_SOCKET){
			err_display("accept()");
			break;
		}

		// 접속한 클라이언트의 IP 주소와 포트 번호 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// 클라이언트가 보낸 데이터를 수신하는 루프
		while(1){
			// 5. recv() : 클라이언트로부터 데이터 수신
			retval = recv(client_sock, buf, BUFSIZE, 0);
			if(retval == SOCKET_ERROR){
				err_display("recv()");
				break;
			}
			else if(retval == 0) // 클라이언트가 연결을 정상 종료했을 때
				break;

			// 받은 데이터의 끝에 문자열 종료 기호('\0')를 붙여 출력
			buf[retval] = '\0';
			printf("%s", buf);
		}

		// 6. closesocket() : 클라이언트 통신 종료 후 통신 소켓 닫기
		closesocket(client_sock);
		printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	}

	// 듣기 소켓 닫기
	closesocket(listen_sock);

	return 0;
}

int main(int argc, char *argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		return 1;

	// 쓰레드 생성하여 TCPServer4 함수 실행
	HANDLE hThread[1];
	hThread[0] = CreateThread(NULL, 0, TCPServer4, NULL, 0, NULL);
	
	// 쓰레드가 종료될 때까지 대기
	WaitForMultipleObjects(1, hThread, TRUE, INFINITE);

	// 윈속 종료
	WSACleanup();
	return 0;
}
