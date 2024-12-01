#include <iostream>
#include <thread>
#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")  // 引入 Winsock 库

// 客户端处理函数
void handleClient(SOCKET clientSocket) {
    char buffer[512];
    int bytesReceived;

    // 循环接收客户端消息
    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        // 输出客户端发送的消息
        std::cout << "Received: " << std::string(buffer, bytesReceived) << std::endl;

        // 发送响应消息
        send(clientSocket, "Hello, Client!", 14, 0);
    }

    // 关闭与客户端的连接
    std::cout << "Client disconnected." << std::endl;
    closesocket(clientSocket);
}

int main() {
    // 初始化 Winsock
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "WSAStartup failed with error: " << wsaResult << std::endl;
        return 1;
    }
    // 创建一个 TCP 套接字
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    //绑定套接字到本地端口
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // 任意 IP 地址
    serverAddr.sin_port = htons(8080);        // 端口号，使用 htons 转换为网络字节序
    int bindResult = bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (bindResult == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    //开始监听连接请求
    int listenResult = listen(serverSocket, 5);
    if (listenResult == SOCKET_ERROR) {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    // 接收客户端连接并为每个客户端创建新线程
    while (true) {
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed." << std::endl;
            continue;
        }
        std::cout << "Client connected." << std::endl;
        // 创建新线程处理客户端请求
        std::thread clientThread(handleClient, clientSocket);
        clientThread.detach();  // 分离线程，让其独立运行
    }
    //关闭套接字并清理资源
    //closesocket(clientSocket);
    //closesocket(serverSocket);
    //WSACleanup();
    return 0;
}