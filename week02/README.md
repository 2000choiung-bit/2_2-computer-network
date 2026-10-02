<img width="1558" height="812" alt="image" src="https://github.com/user-attachments/assets/a09ea0b6-1f5c-4397-adc1-dcf152149603" /># 📡 2주차: TCP 서버 생성 및 데이터 수신 실습

Win32 API 쓰레드와 Winsock2를 사용하여 IPv4 기반의 Basic TCP 서버를 구축하는 예제입니다.

## 💡 핵심 흐름 (소켓 통신 5단계)
1. **`socket()`**: 클라이언트 요청을 수신할 **Listen 소켓** 생성
2. **`bind()`**: 서버의 IP 주소와 포트 번호(`9000`)를 소켓에 결합
3. **`listen()`**: 클라이언트의 접속 요청 대기 상태 진입
4. **`accept()`**: 접속 허가 및 데이터 송수신용 **Client 소켓** 별도 생성
5. **`recv()` / `closesocket()`**: 데이터 수신 처리 후 소켓 종료

## 🔑 주요 개념 및 함수
* **`INADDR_ANY`**: 서버 PC의 모든 네트워크 카드(IP)로 들어오는 요청을 받겠다는 의미
* **`CreateThread()`**: 서버 실행 로직을 별도 쓰레드로 분리하여 비동기로 처리
* <img width="1558" height="812" alt="image" src="https://github.com/user-attachments/assets/dfd4bd4b-bfe2-4e70-8b35-01f131e3a0e6" />
