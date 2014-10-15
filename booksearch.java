#include<stdio.h>
#include<malloc.h>

typedef struct node{//定义节点类型
float coef;
int expn;
struct node * next;
}PLOY;

void start()//用户选择界面
{
printf("************************************\n");
printf(" 两个一元多项式的相加/相减，相乘:\n");
printf("************************************\n");
printf("请选择操作:\n");
printf("0.退出\n");
printf("1.两个一元多项式相加\n");
printf("2.两个一元多项式相乘\n");
printf("3.两个一元多项式相减\n");
}
void insert(PLOY *head,PLOY *inpt)//查找位置插入新链节程序
{
PLOY *pre,*now;
int signal=0;
pre=head;//pre定义为现在的前一个链节
if(pre->next==NULL) {pre->next=inpt;}
else {now=pre->next;
while(signal==0)
{
if(inpt->expn<now->expn)//当新链节小于现在的连接时向后移一个链节
{
if(now->next==NULL)
{
now->next=inpt;
signal=1;
}
else
{
pre=now;
now=pre->next;
}
}
else
if(inpt->expn>now->expn)//如果发现比现在的链节大了就插入到这个连接的前面
{
inpt->next=now;
pre->next=inpt;
signal=1;
}
else
{
now->coef=now->coef+inpt->coef;
signal=1;
free(inpt);//与当前链节相等指数
if(now->coef==0)
{
pre->next=now->next;
free(now);
}
}
}
}
}

PLOY *creat(char ch)//输入多项式
{
PLOY *head,*inpt;
float x;
int y;
head=(PLOY *)malloc(sizeof(PLOY));//创建链表头
head->next=NULL;
printf("请输入一元多项式%c:(格式是：系数 指数；以0 0 结束！)\n",ch);
scanf("%f %d",&x,&y);
while(x!=0)
{
inpt=(PLOY *)malloc(sizeof(PLOY));//创建新链节
inpt->coef=x;
inpt->expn=y;
inpt->next=NULL;
insert(head,inpt);//不然就查找位置并且插入新链节
printf("请输入一元多项式%c的下一项:(以0 0 结束！)\n",ch);
scanf("%f %d",&x,&y);
}
return head;
}

PLOY *addPLOY(PLOY *head,PLOY *pre)//多项式相加
{
PLOY *inpt;
int flag=0;
while(flag==0)
{
if(pre->next==NULL)
flag=1;//当现在指向空时跳出循环
else
{
pre=pre->next;
inpt=(PLOY *)malloc(sizeof(PLOY));//创建新链节
inpt->coef=pre->coef;
inpt->expn=pre->expn;
inpt->next=NULL;
insert(head,inpt);
}//否则把当前"g(x)"的链节插入到"y(x)"中
}
return head;
}

PLOY *minusPLOY(PLOY *head,PLOY *pre)//多项式相jian
{
PLOY *inpt;
int flag=0;
while(flag==0)
{
if(pre->next==NULL)
flag=1;//当现在指向空时跳出循环
else
{
pre=pre->next;
inpt=(PLOY *)malloc(sizeof(PLOY));//创建新链节
inpt->coef=0-pre->coef;
inpt->expn=pre->expn;
inpt->next=NULL;
insert(head,inpt);
}//否则把当前"g(x)"的链节插入到"y(x)"中
}
return head;
}

PLOY *byPLOY(PLOY *head1,PLOY *head2)//多项式相乘
{
PLOY *inpt,*res,*pre;
int flag=0;
res=(PLOY *)malloc(sizeof(PLOY));//创建链表头
res->next=NULL;
head1=head1->next;
pre=head2;
while(flag==0)
{
if(pre->next==NULL)
{
pre=head2;//当现在指向空时跳出循环
head1=head1->next;
continue;
}
if(head1==NULL)
{
flag=1;//当现在指向空时跳出循环
continue;
}
pre=pre->next;
inpt=(PLOY *)malloc(sizeof(PLOY));//创建新链节
inpt->coef=pre->coef*head1->coef;
inpt->expn=pre->expn+head1->expn;
inpt->next=NULL;
insert(res,inpt);//把当前"g(x)"的链节插入到"y(x)"中
}
return res;
}

void print(PLOY *fun)//输出多项式
{
PLOY *printing;
int flag=0;
printing=fun->next;//正在被打印的链节
if(fun->next==NULL)//如果函数为空打印0
{
printf("0\n");
return;
}
while(flag==0)
{
if(printing->coef>0&&fun->next!=printing)
printf("+");//为正数时打印"+"号
if(printing->coef==1);//如果为"1"就不用打印系数了
else if(printing->coef==-1)
printf("-");//如果为"-1"就打印"-"号就行了
else
printf("%f",printing->coef);//其余情况都得打印
if(printing->expn!=0) printf("x^%d",printing->expn);//如果指数为"0"不打印指数项
else if((printing->coef==1)||(printing->coef==-1))
printf("1");
if(printing->next==NULL)
flag=1;//如果现在的链节没有下一个就结束
else
printing=printing->next;
}
printf("\n");
}

void main()
{
PLOY *f,*g;
int sign=-1;//设置标志
start();
while(sign!=0)
{
scanf("%d",&sign);
switch(sign)
{
case 0:
break;//退出
case 1:
{
printf("你选择的操作是多项式相加:\n");
f=creat('f');//输入多项式f(x)
printf("f(x)=");
print(f);
g=creat('g');//输入多项式g(x)
printf("g(x)=");
print(g);
printf("F(x)=f(x)+g(x)=");
f=addPLOY(f,g);//两个多项式相加
print(f);
sign=-1;//复位标志
start();//回复用户选择界面
break;
}
case 2:
{
printf("你选择的操作是多项式相乘:\n");
f=creat('f');//输入多项式f(x)
printf("f(x)=");
print(f);
g=creat('g');//输入多项式g(x)
printf("g(x)=");
print(g);
printf("F(x)=f(x)*g(x)=");
f=byPLOY(f,g);//两个多项式相加
print(f);
sign=-1;//复位标志
start();//回复用户选择界面
break;
}
case 3:
{
printf("你选择的操作是多项式相减:\n");
f=creat('f');//输入多项式f(x)
printf("f(x)=");
print(f);
g=creat('g');//输入多项式g(x)
printf("g(x)=");
print(g);
printf("F(x)=f(x)-g(x)=");
f=byPLOY(f,g);//两个多项式相加
print(f);
sign=-1;//复位标志
start();//回复用户选择界面
break;
}

default:
{
printf("输入有误!请重新选择操作!\n");//选择错误,返回选择界面
start();
break;
}
}
}
}


