#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count(char a[], char w[][10], int n, int b[]) {
    char* word = strtok(a, " ,.");//strtok为库函数，第一个参数是需要截取的原字符串，第二个参数是分隔符字符串，只需要把分隔符连在一起输入即可
    while (word != NULL) {
        for (int i = 0; i < n; i++) {
            if (strcmp(word, w[i]) == 0) {
                b[i]++;
            }
        }
        word = strtok(NULL, " ,.");
    }
}
int main() {
    char a[] = "this is a book, that is an apple";
    char w[][10] = {"is", "that"};
    int n = 2;
    int b[n];
    memset(b, 0, sizeof(b));//sizeof函数对数组名使用时可以得到数组长度
    //memset函数用来填充数组，用第二个参数，填充长度为第三个参数
    count(a, w, n, b);
    for (int i = 0; i < n; i++) {
        printf("%s:%d ", w[i], b[i]);
    }
    return 0;
}

