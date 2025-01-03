#include<stdio.h>
#include<conio.h>
#include<string.h>
typedef struct {
 char  name[10], degree[10];
}ST;/*要用typedef*/
void sort(ST x[],int n,char key[][10],int m)
{   
int i,j,k,con1,con2;    
    	ST v;
    	for(i=0;i<n-1;i++)
      for(j=0;j<n-i-1;j++) { //冒泡排序，接下来是“比较、交换”的实现
 for(k=0;k<m;k++)
	             if(strcmp(x[j].degree,key[k])==0){
 	    con1=k;
break;
   }
	         for(k=0;k<m;k++)
	       	    if(strcmp(x[j+1].degree,key[k])==0){
	con2=k;
 break; 
}
	         if(con1>con2||con1==con2&&strcmp(x[j].name,x[j+1].name)>0){/*交换条件写反了，name的判断改为大于*/
 v=x[j];
 x[j]=x[j+1];
 x[j+1]=v;
 }
  	   }
}
int main(void)
{  
ST s[5]={{"Andy","master"},{"Beth","bachelor"},{"Can","doctor"},
            {"Deo","bachelor"},{"Emy","master"}};
  	char sortkey[3][10]={"bachelor","master","doctor"};/*sortkey是每个元素最长10，元素个数可变的关键词数组，是二维数组*/
  	int i;
  sort(s,5,sortkey,3);
  	for(i=0;i<5;i++)
         printf("\n%s    %s",s[i].name,s[i].degree);/*用结构名访问成员使用.而不是->*/
  	return 0;
} 
