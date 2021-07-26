#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>



using namespace std;

int main() {

	cout << "-------------TCP Client-------------" << endl;

	WSADATA WinSockData;
	int iWSAStartup;
	int iWSACleanup;

	SOCKET TCPClientSocket;
	int iCloseSocket;

	struct sockaddr_in TCPServerAddress;

	int iConnect;

	int iListen;

	int iReceive;
	char receiverBuffer[512];
	int iReceiverBuffer = strlen(receiverBuffer) + 1;


	int iSend;
	char senderBuffer[512] = "Hello from Client";
	int iSenderBuffer = strlen(senderBuffer) + 1;



	// 1 starting up the windows socket dll

	iWSAStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);
	if (iWSAStartup != 0) {
		cout << "WSA Startup failed" << endl;
	}
	cout << "WSA Startup success" << endl;


	// 2 filling the structure of server

	TCPServerAddress.sin_family = AF_INET;
	TCPServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	TCPServerAddress.sin_port = htons(8000);//little endian to big endian conversion

	// 3 Create a client side socket

	TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (TCPClientSocket == INVALID_SOCKET) {
		cout << "TCP client socket creation failed" << WSAGetLastError() << endl;
	}

	cout << "TCP client socket created" << endl;

	//4 Connecting to server socket

	iConnect = connect(TCPClientSocket, (SOCKADDR*)&TCPServerAddress, sizeof(TCPServerAddress));

	if (iConnect == SOCKET_ERROR) {
		cout << "Not connecting. Error code: " << WSAGetLastError() << endl;
	}
	cout << "Connected" << endl;


	//5 Receive data from server side using recv function
	iReceive = recv(TCPClientSocket, receiverBuffer, iReceiverBuffer, 0);

	if (iReceive == SOCKET_ERROR) {
		cout << "Receiving from the server socket failed" << WSAGetLastError() << endl;
	}
	cout << "Data received from the server socket" << receiverBuffer << endl;


	//6 Send data to server using send() function
	iSend = send(TCPClientSocket, senderBuffer, iSenderBuffer, 0);// should send client socket as parameter. not tcpserversocket

	if (iSend == SOCKET_ERROR) {
		cout << "Sending to the server socket failed" << WSAGetLastError() << endl;
	}
	cout << "Data sent to the server socket" << endl;

	//9 close socket
	iCloseSocket = closesocket(TCPClientSocket);
	if (iCloseSocket == SOCKET_ERROR) {
		cout << "Closing TCP server socket failed" << WSAGetLastError() << endl;
	}
	cout << "Closed TCP server socket" << endl;

	//10 wsa cleanup

	iWSACleanup = WSACleanup();
	if (iWSACleanup == SOCKET_ERROR) {
		cout << "WSA Cleanup failed" << WSAGetLastError() << endl;
	}

	cout << "WSA Cleaned up" << endl;

	return 0;
}