#include<graphics.h> 
#include<stdio.h>
#include<conio.h>
int main()
{
    int option; // 选项变量
    initgraph(640, 480); // 创建窗口
    do {
        cleardevice(); // 清屏
        // 绘制主菜单
        outtextxy(280, 200, "主人今天想画什么喵？");
        outtextxy(280, 220, "1. 圆形");
        outtextxy(280, 240, "2. 矩形");
        outtextxy(280, 260, "3. 椭圆形");
        outtextxy(280, 280, "4. 扇形");
        outtextxy(280, 300, "0. 退出程序");

        // 读取用户输入的选项
        option = getch();

        // 根据选项绘制对应的图形
        switch (option) {
        case 1:
            circle(320, 240, 100); // 绘制圆形
            break;
        case 2:
            rectangle(220, 140, 420, 340); // 绘制矩形
            break;
        case 3:
            ellipse(320, 240, 100, 60); // 绘制椭圆形
            break;
        case 4:
            pieslice(320, 240, 0, 120, 100); // 绘制扇形
            break;
        }
        // 返回主菜单的选项
        if (option != 0) {
            outtextxy(280, 320, "按任意键返回主菜单");
            getch(); // 消除此按键
        }
    } while (option != 0); // 选0时退出循环
    closegraph(); // 关闭窗口
    return 0;
}
