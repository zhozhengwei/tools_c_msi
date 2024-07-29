#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isConnectedToLocalNetwork() {
    // 要 ping 的目标主机或者 IP 地址，可以是局域网内的某个设备或者网关
    const char *targetHost = "10.101.0.10"; // 替换为实际的目标 IP 地址

    // 构建执行的命令
    char command[256];
    sprintf(command, "ping -n 1 %s", targetHost); // 使用 -n 1 表示只发送一次 ping 请求

    // 执行 ping 命令并获取输出
    FILE *fp = _popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return false;
    }

    char buffer[128];
    bool connected = false;

    // 读取 ping 命令的输出
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // 检查输出中是否包含 Reply 字符串，表示成功收到 ping 回复
        if (strstr(buffer, "Reply") != NULL) {
            connected = true;
            break;
        }
    }

    // 关闭文件指针
    _pclose(fp);

    return connected;
}

void writeConnectionStatus(bool connected) {
    // 打开文件进行写入
    FILE *file = fopen("connected.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // 根据连接状态写入 0 或 1
    if (connected) {
        fprintf(file, "0\n");
    } else {
        fprintf(file, "1\n");
    }

    // 关闭文件
    fclose(file);
}

int main() {
    bool connected = isConnectedToLocalNetwork();
    writeConnectionStatus(connected);
    return 0;
}
