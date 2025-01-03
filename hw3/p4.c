#include<stdio.h>
#include<graphics.h>
int main(){
    int a,b,c,d,e,f,g,h,k,l,m
    double i,j;
    scanf("%d%d%d%d%d%d%d%d%f%f%d%d%d",&a,&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l,&m);
    initgraph(1024,768);
    setlinecolor(RED);
    rectangle(a,b,c,d);
    pie(e,f,g,h,i,j);
    circle(k,l,m);
    closegraph();
}