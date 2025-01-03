#include<stdio.h>
#include<string.h>

int replace_str(char *s, char *t, char *g) {
    int count = 0;
    int t_len = strlen(t);
    int g_len = strlen(g);
    char *pos = strstr(s, t); // 查找t在s中第一次出现的位置
    while (pos) {
        count++;
        memmove(pos + g_len, pos + t_len, strlen(pos + t_len) + 1); // 后面的字符向后移动
        memcpy(pos, g, g_len); // 复制g到替换的位置
        pos = strstr(pos + g_len, t); // 继续查找下一个t
    }
    return count;
}

int main(){
    char s[100],t[100],g[100];
    int ans=0;
    scanf("%s %s %s",s,t,g);
    ans=replace_str(s,t,g);
    printf("%s\ncount=%d",s,ans);
}