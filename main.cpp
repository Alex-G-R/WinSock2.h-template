#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma  comment(lib, "ws_32.lib")
#include <iostream>
#include <string>
#include <WinSock2.h>

using std::string;

int main()
{
    std::cout << "Creating a web server \n";

    SOCKET wsocket;
    SOCKET new_wsocket;
    WSADATA wsaData;
    struct sockaddr_in server;
    int server_len;
    int BUFFER_SIZE = 30720;

    // Initialize
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "Could not initialize \n";
    }

    // Create a socket
    wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(wsocket == INVALID_SOCKET)
    {
        std::cout << "Could not create a socket \n";
    }

    // Bind socket to address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(3000);
    server_len = sizeof(server);

    if(bind(wsocket, (SOCKADDR *)&server, server_len) != 0)
    {
        std::cout << "Could not bind socket \n";
    }

    // Listen to address
    if(listen(wsocket, 20) != 0)
    {
        std::cout << "Could not start listening to adress \n";
    }

    std::cout << "Listening on 127.0.0.1:3000 \n";

    int bytes = 0;
    while(true)
    {
        // Accept client request
        new_wsocket = accept(wsocket, (SOCKADDR*)&server, &server_len);
        if(new_wsocket == INVALID_SOCKET)
        {
            std::cout << "Could not accept client request\n";
        }

        // Read client request
        char buff[30720] = { 0 };
        bytes = recv(new_wsocket, buff, BUFFER_SIZE, 0);
        if(bytes < 0)
        {
            std::cout << "Could not read client data \n";
        }

        // Send response to client
        string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
        string response = "<html><h1>Hello C++!</h1></html>";
        serverMessage.append(std::to_string(response.size()));
        serverMessage.append("\n\n");
        serverMessage.append(response);

        int bytesSent = 0;
        int totalBytesSent = 0;
        while(totalBytesSent < serverMessage.size())
        {
            bytesSent = send(new_wsocket, serverMessage.c_str(), serverMessage.size(), 0);
            if(bytes < 0)
            {
                std::cout << "Could not send response";
            }

            totalBytesSent += bytesSent;
        }
        std::cout << "Sent response to client \n";

        closesocket(new_wsocket);
    }

    closesocket(wsocket);
    WSACleanup();

    return 0;
}
