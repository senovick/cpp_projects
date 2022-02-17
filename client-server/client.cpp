#include <iostream>
#include <winsock2.h>

using namespace std;

int main(){
    
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	
	printf("Initialised.\n");
	
	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");
	
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    //Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		cerr << "Can't connect to server " << WSAGetLastError() << endl;
		return 1;
	}
	
	puts("Connected");
	
	//Send some data
	char buf[4096];
    string userInput;

    do
    {
        cout << "> ";
        getline(cin, userInput);
        int sendResult = send(s, userInput.c_str(), userInput.size() + 1, 0);

        if(sendResult != SOCKET_ERROR)
        {
            ZeroMemory(buf, 4096);
            int bytesReceived = recv(s, buf, 4096, 0);
            if(bytesReceived > 0)
            {
                cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
            }
        }
    } while(userInput.size() > 0);

    closesocket(s);
    WSACleanup();
    return 0;
}