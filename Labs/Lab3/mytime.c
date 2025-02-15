#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main() {
    struct timeval tv;
    time_t curr_time;
    char *time_str;

    // get time of day
    if (gettimeofday(&tv, NULL) == -1) {
        perror("gettimeofday");
        return 1;
    }

    // extract seconds from timeval struct
    curr_time = tv.tv_sec;

    // use ctime to convert to string
    time_str = ctime(&curr_time);
    if (time_str == NULL) {
        perror("ctime");
        return 1;
    }

    printf("Current time: %s\n", time_str);

    return 0;
}