#include <stdio.h>
#include <time.h>

// 假设你有两个时间点
time_t time1 = 1673289200; // 2023-01-01 00:00:00 UTC
time_t time2 = 1673375600; // 2023-01-02 00:00:00 UTC

int main() {
    // 计算时间差
    time_t time_diff = time2 - time1;

    // 输出时间差（以秒为单位）
    printf("时间差为：%ld 秒\n", time_diff);

    // 如果你想要将时间差转换为更易读的格式，比如天数、小时数等
    double days = time_diff / (24.0 * 60.0 * 60.0);
    double hours = time_diff / (60.0 * 60.0);
    double minutes = time_diff / 60.0;

    printf("时间差为：%.2f 天\n", days);
    printf("时间差为：%.2f 小时\n", hours);
    printf("时间差为：%.2f 分钟\n", minutes);

    return 0;
}