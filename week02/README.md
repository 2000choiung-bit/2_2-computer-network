# 📡 2주차: TCP 서버 생성 및 데이터 수신 실습

교수님 공지사항 예제 코드를 분석하고 직접 실행해 본 실습 기록입니다.

---

## 📌 주요 코드 및 개념 분석
* **`socket()`**: 클라이언트 요청을 수신할 **Listen 소켓** 생성
* **`bind()`**: 서버의 IP 주소와 포트 번호(`9000`)를 소켓에 결합
* **`listen()`**: 클라이언트의 접속 요청 대기 상태 진입
* **`accept()`**: 접속 허가 및 데이터 송수신용 **Client 소켓** 별도 생성
* **`recv()`**: 클라이언트가 보낸 메시지를 읽어와 콘솔에 출력

---

## ❓ 에러 해결 과정 (Troubleshooting)

C++ 컴파일 도중 C2664, C4996 오류가 발생하여 다음과 같이 수정을 진행했습니다.

* **💡 핵심 수정 포인트 2가지**
  1. **`#define _WINSOCK_DEPRECATED_NO_WARNINGS` 상단 이동:**
     * `#include <winsock2.h>`보다 **무조건 상단**으로 배치하여 구버전 윈속 함수(inet_ntoa 등) 사용 시 발생하는 C4996 컴파일 경고/오류를 방지했습니다.
  2. **`const` 키워드 추가:**
     * `void err_quit(char *msg)` ➔ **`void err_quit(const char *msg)`**
     * C++ 표준 문법 엄격성 강화로 인해 문자열 리터럴 전달 시 발생하던 C2664 오류를 해결했습니다.

---

## 📸 실행 결과 화면


> **설명:** 서버 프로그램 실행 후 PowerShell/cmd에서 9000번 포트로 연결하여 메시지를 수신한 성공 화면입니다.
<img width="1558" height="812" alt="image" src="https://github.com/user-attachments/assets/dfd4bd4b-bfe2-4e70-8b35-01f131e3a0e6" />
