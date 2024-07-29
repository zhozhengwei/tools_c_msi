#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") 


#define SERVER_IP "10.101.0.10" // 内网服务器的IP地址
#define SERVER_PORT 12345       // 内网服务器的端口号
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int n;

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return 1;
    }

    // 创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connection to the server failed with error: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // 从服务器读取时间数据
    if ((n = recv(sockfd, buffer, BUFFER_SIZE - 1, 0)) == SOCKET_ERROR) {
        printf("Read from server failed with error: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    buffer[n] = '\0'; // Null-terminate the received string

    // 解析服务器返回的时间
    int year, month, day, hour, minute, second;
    if (sscanf(buffer, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {
        fprintf(stderr, "Failed to parse time from server\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // 打开文件
    FILE *file = fopen("time.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // 写入日期和时间到文件
    fprintf(file, "%02d-%02d-%04d\n", month, day, year);
    fprintf(file, "%02d:%02d:%02d\n", hour, minute, second);

    // 关闭文件
    fclose(file);

    // 关闭套接字
    closesocket(sockfd);

    // 清理 Winsock
    WSACleanup();

    return 0;
}
