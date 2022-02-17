#include <iostream>
#include <winsock2.h>

using namespace std;

int main(){
    
    WSADATA wsa;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsa);
    if(wsOk != 0)
    {
        cerr << "Can't Initialize winsock! Quitting" << endl;
        return 1;
    }
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == INVALID_SOCKET)
    {
        cerr << "Can't create socket! Quitting" << endl;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(8888);
    hint.sin_addr.s_addr = INADDR_ANY;

    if(bind(listening, (struct sockaddr *)&hint, sizeof(hint)) == SOCKET_ERROR)
    {
        cerr << "Bind failed with error code " << WSAGetLastError() << endl;
        return 1;
    }

    cout << "Bind Complete" << endl;

    listen(listening, 5);
    cout << "Waiting for incoming connections..." << endl;
    sockaddr_in client;
    int clientSize = sizeof(client);
    SOCKET clientSocket = accept(listening, (struct sockaddr *)&client, &clientSize);
    
    char buf[4096];
    while(clientSocket != INVALID_SOCKET )
    {
        ZeroMemory(buf, 4096);

        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if(bytesReceived == SOCKET_ERROR)
        {
            cerr << "Error in receving bytes" << endl;
            break;
        }
        if(bytesReceived == 0)
        {
            cerr << "No bytes received...client disconnected" << endl;
        }

        send(clientSocket, buf, bytesReceived + 1, 0);
    }
    
    if(clientSocket == INVALID_SOCKET)
    {
        cerr << "Accept failed with error" << WSAGetLastError() << endl;
    }

    cout << "Connection accepted" << endl;

    closesocket(listening);
    WSACleanup();
    return 0;
}