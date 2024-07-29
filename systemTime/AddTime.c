#include <stdio.h>
#include <time.h>
#include <Windows.h>

void add_one_hour_to_system_time() {
    time_t now;
    struct tm new_time;
    SYSTEMTIME st;
    SYSTEMTIME temp;
    SYSTEMTIME st1;
    SYSTEMTIME temp1;
    GetLocalTime(&st);  // 获取当前本地时间
    GetLocalTime(&temp);
    // 增加一个小时
    st.wHour += 1;

    // 如果小时超过 23，增加到下一天，并重新设置小时
    if (st.wHour >= 24) {
        st.wHour -= 24;
        temp.wHour=st.wHour+4;
        temp.wDay += 1;
    }else{
        temp.wHour = st.wHour - 8;
    }
    
        // 设置系统时间
    if (!SetSystemTime(&temp)) {
        fprintf(stderr, "Failed to set system time\n");
    } else {
        printf("System time updated successfully\n");
    }

    time(&now);
    new_time = *localtime(&now);
     // 输出新时间（格式：YYYY-MM-DD HH:MM:SS）
    printf("%04d/%02d/%02d %02d:%02d:%02d\n",
           new_time.tm_year + 1900,
           new_time.tm_mon + 1,
           new_time.tm_mday,
           new_time.tm_hour,
           new_time.tm_min,
           new_time.tm_sec);
}

int main() {
    add_one_hour_to_system_time();
    return 0;
}
