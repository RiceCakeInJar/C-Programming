#include<stdio.h>



void getDigits(char *s1,char *s2)

{

while(*s1)

{

if(*s1>='0'&&*s1<='9')

{

{*s2=*s1;s2++;}

s1++;

}

}

*s2='\0';

}



void main()

{

char s1[50],s2[50];

printf("Input s1:");

gets(s1);

getDigits(s1,s2);

printf("\n%s",s2);

}
