#include <stdio.h>
#include <windows.h>

void set_time_zone(const wchar_t* time_zone_id) {
    TIME_ZONE_INFORMATION tz_info;
    DYNAMIC_TIME_ZONE_INFORMATION dtz_info;

    // Get the current time zone information
    if (GetTimeZoneInformation(&tz_info) == TIME_ZONE_ID_INVALID) {
        printf("Failed to get current time zone information\n");
        return;
    }

    // Get the dynamic time zone information
    if (GetDynamicTimeZoneInformation(&dtz_info) != 0) {
        printf("Failed to get dynamic time zone information\n");
        return;
    }

    // Set the time zone ID to the desired time zone
    wcsncpy(dtz_info.TimeZoneKeyName, time_zone_id, sizeof(dtz_info.TimeZoneKeyName) / sizeof(wchar_t) - 1);

    // Set the dynamic time zone information
    if (SetDynamicTimeZoneInformation(&dtz_info)) {
        printf("Time zone successfully set to %ls\n", time_zone_id);
    } else {
        printf("Failed to set time zone\n");
    }
}

int main() {
    const wchar_t* tokyo_time_zone_id = L"Tokyo Standard Time";
    set_time_zone(tokyo_time_zone_id);
    return 0;
}
