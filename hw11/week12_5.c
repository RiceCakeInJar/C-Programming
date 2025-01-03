#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
long stoi(char *s,int *i)//第一个错误：void改为long
{	
    long n=0;
	while(isdigit(s[(*i)]))
	   	n=n*10+s[(*i)++]-('1'-1);//第二个错误：后面加上“-('1'-1)”，因为某个数字的字符对应的数和它本身的数值相差('1'-1)
	return n;
}
long add(char *s)
{	
    int i=0,*pi=&i;//第三个错误：改为*pi=&i
	char op;	
    long a=0,b=0,c;
	a=stoi(s,pi);
	op=s[i++];
	b=stoi(s,pi);
	switch(op) {
		case '+':return a+b;
		case '-':return a-b;
		case '*':return a*b;
		case '/':if(b==0) {printf("div!0");exit(0);}//第四个错误：添加{}，防止错误调用exit(0)
                 return a/b;
		default: printf("operator error!");exit(0);
	}
}
int main(void)
{	
    char s[80];
	gets(s);
    printf("%s=",s);
	printf("%ld\n",add(s));
	return 0;
}
