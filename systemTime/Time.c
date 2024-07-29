#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void adjust_time(int add_hours) {
    time_t rawtime;
    struct tm *timeinfo;

    // 获取当前系统时间
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // 输出当前系统时间
    printf("Current local time and date: %s", asctime(timeinfo));

    // 调整小时
    timeinfo->tm_hour += add_hours;

    // 处理小时溢出
    if (timeinfo->tm_hour >= 24) {
        timeinfo->tm_hour -= 24;
        timeinfo->tm_mday += 1;
        
        // 检查日期溢出（天数可能超过一个月的天数）
        mktime(timeinfo);
    } else if (timeinfo->tm_hour < 0) {
        timeinfo->tm_hour += 24;
        timeinfo->tm_mday -= 1;

        // 检查日期溢出（可能跨月减一天）
        mktime(timeinfo);
    }

    // 输出新的时间
    printf("Adjusted local time and date: %s", asctime(timeinfo));

    // 设置系统时间
    time_t new_rawtime = mktime(timeinfo);
    if (new_rawtime != -1) {
        if (settimeofday(&new_rawtime, NULL) == 0) {
            printf("System time adjusted successfully.\n");
        } else {
            perror("Failed to set system time");
        }
    } else {
        fprintf(stderr, "Failed to convert time.\n");
    }
}

int main() {
    // 调快一小时
    adjust_time(1);

    return 0;
}
