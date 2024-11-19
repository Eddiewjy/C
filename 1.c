#include <stdio.h>
#include <string.h>

void removeAllSubstr(char *s, const char *t) {
    int sLen = strlen(s);
    int tLen = strlen(t);
    int i, j;

    if (tLen == 0)
        return; // 如果 t 为空，直接返回 s

    // 遍历字符串 s，删除所有匹配的子串 t
    for (i = 0; i <= sLen - tLen;) {
        // 检查从 s[i] 开始的子串是否与 t 相同
        if (strncmp(&s[i], t, tLen) == 0) {
            // 如果匹配，将 s 中 t 后面的字符向前移动 tLen 个位置
            for (j = i; j <= sLen - tLen; j++) {
                s[j] = s[j + tLen];
            }
            // 更新 s 的新长度
            sLen -= tLen;
            s[sLen] = '\0';
        } else {
            // 如果不匹配，继续扫描下一个字符
            i++;
        }
    }
}

int main() {
    char s[100] = "hello world, hello everyone";
    const char t[] = "hello";

    printf("Original String (s): %s\n", s);
    removeAllSubstr(s, t);
    printf("Modified String (s): %s\n", s);

    return 0;
}
