#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char* argv[]) {
    time_t now;
    struct tm new_time;

    const char *add = argv[1];

    int addnumber = atoi(add);
    // 获取当前时间
    time(&now);
    new_time = *localtime(&now);

    // 增加n小时
    new_time.tm_hour += addnumber;

    // 处理时间溢出
    mktime(&new_time);

    // 输出新时间（格式：YYYY-MM-DD HH:MM:SS）
    printf("%04d/%02d/%02d %02d:%02d:%02d\n",
           new_time.tm_year + 1900,
           new_time.tm_mon + 1,
           new_time.tm_mday,
           new_time.tm_hour,
           new_time.tm_min,
           new_time.tm_sec);

    return 0;
}
