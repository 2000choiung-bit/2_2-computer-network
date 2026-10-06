// TCP Client Fixed
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    50
void err_quit(const char* msg) { printf("[%s]", msg); exit(1); }
void err_display(const char* msg) { printf("[%s]", msg); }
int main(int argc, char* argv[])
{
	int retval;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");
	char buf[BUFSIZE];
	char* testdata[] = {
	"안녕하세요",
	"좋은 아침입니다",
	"통신을 배운다는 것은 참 좋은 일입니다",
	"맞습니다",
	};
	for (int i = 0; i < 4; i++) {
		memset(buf, '#', sizeof(buf));
		strncpy(buf, testdata[i], strlen(testdata[i]));
		retval = send(sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}
		printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval);
	}
	closesocket(sock);
	WSACleanup();
	getchar();
	return 0;
}