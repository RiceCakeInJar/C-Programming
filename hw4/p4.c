#include <stdio.h>
#include<stdlib.h>
int main() {
    double I, bonus;

    printf("�����뵱��������Ԫ����");
    scanf("%lf", &I);

    switch ((int)I / 100000) {
        case 0:
            bonus = I * 0.1;
            break;
        case 1:
            bonus = 10000 + (I - 100000) * 0.075;
            break;
        case 2:
        case 3:
            bonus = 17500 + (I - 200000) * 0.05;
            break;
        case 4:
        case 5:
            bonus = 27500 + (I - 400000) * 0.03;
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            bonus = 33500 + (I - 600000) * 0.015;
            break;
        default:
            bonus = 39500 + (I - 1000000) * 0.01;
            break;
    }

    printf("Ӧ���Ž�������Ϊ��%.2lf��Ԫ\n", bonus);
	system("pause");
}
