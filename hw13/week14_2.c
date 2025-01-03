/*
⑴ 自定义结构类型用于存储以下联系人信息，用typedef将类型标识符定义为PS。
       long  id  ：        	学号
       char name[10]： 		姓名
       char sex[2] ：      	性别（m 代表男，f 代表女）
⑵ 编写函数int delete(PS *p1, int m, PS *p2,int n) 。 p1指向数组中保存m个联系人信息， p2指向数组中保存n个联系人信息。从p1数组中删除在p2数组中重复出现的联系人信息(id值相同)。返回值为执行删除操作后p1数组中保存的联系人信息的数量。
⑶ 编写函数int merge(PS *p1,int m, PS *p2 ,int n) 。p1指向数组中保存m个联系人信息， p2指向数组中保存n个联系人信息。将p2数组中n个联系人信息合并到p1数组中。已知p1和p2数组中存储的联系人信息按成员id升序排列，合并后p1数组中的联系人信息仍按id升序排列。返回值为合并后p1数组中联系人信息的数量。
⑷ 编写函数void sort(PS *p,int n)，对p指向的数组中的n个联系人信息排序。要求：按性别排序（f在前m在后，f的编码小于m的编码），性别相同的按姓名排序（字典序）。
⑸ 编写函数void display(PS *p,int n)， 将p指向的数组中存储的n个联系人信息输出到显示器（第一行显示标题，以后每行显示一个联系人信息）。
⑹ 编写main函数，声明结构数组a、b并用测试数据初始化（a、b数组中数据按成员id值升序存储；显示a,b数组中数据(显示数组数据调用display函数完成，下同)；调delete函数从a数组中删除在b数组中重复出现的联系人信息，显示a数组中数据；调merge函数将a数组中全部联系人信息合并到b数组，显示b数组中数据；调sort函数对a数组中数据排序，显示a数组中数据。
【测试数据】
a数组：{101, "tom","m"},{103,"mary","f"},{104,"mark","m"}, 
{105,"julia","f"},{106, "sara","f"}
   b数组： {102, "mark","m"},{104,"mark","m"}
【输出结果】
a:
ID      NAME    SEX
101     tom     m
103     mary    f
104     mark    m
105     julia   f
106     sara    f
b:
ID      NAME    SEX
102     mark    m
104     mark    m
a:
ID      NAME	SEX
101     tom     m
103     mary    f
105     julia    	f
106     sara    	f
b:
ID      NAME	SEX
101     tom     m
102     mark    m
103     mary    f
104     mark    m
105     julia    	f
106     sara    	f
 a:
ID		NAME	SEX
105     julia    	f
103     mary    f
106     sara     f
101     tom     m
*/

#include<stdio.h>
#include<string.h>

typedef struct{
    long id;
    char name[10];
    char sex[2];
}PS;

int delete(PS *p1, int m, PS *p2, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (p1[j].id == p2[i].id) {
                for (int k = j; k < m - 1; k++) {
                    p1[k] = p1[k + 1];
                }
                m--; 
            }
        }
    }
    return m;
}

int merge(PS *p1,int m, PS *p2 ,int n){
    n=delete(p2,n,p1,m);
    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(j==m-1){
                p1[m]=p2[i];
            }
            else if(p1[j].id>p2[i].id){
                for(int k=m;k>=j;k--){
                    p1[k+1]=p1[k];
                }
                p1[j]=p2[i];
                break;
            }
        }
        m++;
    }
    return m;
}

void sort(PS *p, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(p[j].sex, p[j + 1].sex) > 0) {
                PS temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
            else if (strcmp(p[j].sex, p[j + 1].sex) == 0) {
                if (strcmp(p[j].name, p[j + 1].name) > 0) {
                    PS temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
    }
}

void display(PS *p, int n) {
    printf("ID\tNAME\tSEX\n");
    for (int i = 0; i < n; i++) {
        printf("%ld\t%s\t%s\n", p[i].id, p[i].name, p[i].sex);
    }
}

int main() {
    PS a[100] = {
        {101, "tom", "m"},
        {103, "mary", "f"},
        {104, "mark", "m"},
        {105, "julia", "f"},
        {106, "sara", "f"}
    };
    PS b[100] = {
        {102, "mark", "m"},
        {104, "mark", "m"}
    };
    int m = 5;
    int n = 2;
    printf("a:\n");
    display(a, m);
    printf("b:\n");
    display(b, n);
    m = delete(a,m,b,n);
    printf("a:\n");
    display(a, m);
    n = merge(b,n,a,m);
    printf("b:\n");
    display(b, n);
    sort(a, m);
    printf("a:\n");
    display(a, m);
    return 0;
}
