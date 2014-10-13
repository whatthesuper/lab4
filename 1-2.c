#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 100
#define M 2*N-1

typedef struct
{
    char data;
    int weight;
    int parent;
    int lchild;
    int mchild;
    int rchild;
} HuffmanTree[M];

typedef struct               //�������������ṹ������
{
    char data;
    char bits[N];
} HuffmanCode[N];

typedef struct str           //�����ַ����洢��Ԫ�ṹ������
{
    char data;
    char num;
    //int num;
} str;

int read(str s2[])
{
    FILE *fp;
    char ch;
    int i,k;
    str s1[128];
    for(i=0; i<=128; i++)
    {
        s1[i].num = 0;
        s1[i].data = 0;
        s2[i].num = 0;
        s2[i].data = 0;
    }

    if((fp=fopen("D://pad1.txt","r"))==NULL)
    {
        printf("\n�ļ�������!");
        exit(1);
    }
    printf("\n��ȡ�ַ���Ϊ:\n");
    ch=fgetc(fp);
    while(!feof(fp))                     //ͳ���ַ�Ƶ��
    {
        printf("%c",ch);
        s1[ch].num++;
        s1[ch].data = ch;
        ch=fgetc(fp);
    }
    fclose(fp);
    for(i=1,k=1; i<=128; i++)
    {
        if(s1[i].num!=0)
        {
            s2[k].num = s1[i].num;
            s2[k].data = s1[i].data;
            k++;
        }
    }
    printf("\n\nͳ�ƽ��Ϊ(�ַ� Ƶ��):\n");
    for(i=1; i<k; i++)
    {
        printf("<%c  %d>  ",s2[i].data,s2[i].num);
    }
    printf("   (��%d���ַ�)\n",k-1);
    return k;
}

void SelectMin(HuffmanTree ht, int i,int *p1,int *p2,int *p3)    //���ҹ���������������Ȩֵ��С�Ľڵ�
{
    int j,min1,min2,min3,number=0;
    min1 = min2 =min3= -1;
    for(j = 1; j<=i; j++)
    {
        if(ht[j].parent == 0)
        {
            if(ht[j].weight<min1||min1==-1)
            {
                if(min1!=-1)
                {
                    min2 = min1;
                    *p2=*p1;
                }
                min1 = ht[j].weight;
                *p1=j;
            }
            else if(ht[j].weight<min2||min2==-1)
            {
                if(min2!=-1)
                {
                    min3 = min2;
                    *p3=*p2;
                }
                min2 = ht[j].weight;
                *p2=j;
            }
            else if(ht[j].weight<min3||min3==-1)
            {
                min3 = ht[j].weight;
                *p3=j;
            }
        }
    }
    if(min3==-1)
        *p3=-1;
}
void CrtHuffmanTree(HuffmanTree ht,str s[],int *n)     //������������
{
    int i,m,p1,p2,p3,mm,flag;
    for(i=1; i<*n; i++)                                //��ʼ���ڵ�
    {
        ht[i].data = s[i].data;
        ht[i].weight = s[i].num;
        ht[i].parent = 0;
        ht[i].lchild = 0;
        ht[i].mchild = 0;
        ht[i].rchild = 0;
    }
    m=((*n)-1)/3;
    if(((*n)-1)%3!=0)
        m++;
    mm=m;
    while(mm!=1)
    {
        if(mm>3)
            flag=mm;
    if(mm%3!=0)
        mm=mm/3+1;
       else mm=mm/3;
       m=m+mm;
    }
    m=m+*n-2;
    if(flag!=5)
        flag=1;
     if(flag==1)
     {
         ht[*n].data = -1;
        ht[*n].weight = 0;
        ht[*n].parent = 0;
        ht[*n].lchild = 0;
        ht[*n].mchild = 0;
        ht[*n].rchild = 0;
     *n=(*n)+1;
     }

     printf("\\");
    for(i=*n; i<=m; i++)
    {
        ht[i].data = 0;
        ht[i].weight = 0;
        ht[i].parent = 0;
        ht[i].lchild = 0;
        ht[i].mchild = 0;
        ht[i].rchild = 0;
    }
    for(i=*n; i<=m; i++)
    {
        SelectMin(ht,i-1,&p1,&p2,&p3);                     //����SelectMin����
        if(p3!=-1)
        {
            ht[i].weight=ht[p1].weight+ht[p2].weight+ht[p3].weight;
            ht[p1].parent=i;
            ht[p2].parent=i;
            ht[p3].parent=i;
            ht[i].lchild=p1;
            ht[i].mchild=p2;
            ht[i].rchild=p3;
        }
        else
        {
            ht[i].weight=ht[p1].weight+ht[p2].weight;
            ht[p1].parent=i;
            ht[p2].parent=i;
            ht[i].lchild=p1;
            ht[i].mchild=-1;
            ht[i].rchild=p2;ht[i].weight=ht[p1].weight+ht[p2].weight+ht[p3].weight;
        ht[p1].parent=i;
        ht[p2].parent=i;
        ht[p3].parent=i;
        ht[i].lchild=p1;
        ht[i].mchild=p2;
        ht[i].rchild=p3;
        }
    }
}

void CrtHuffmanCode(HuffmanTree ht,HuffmanCode hc,int k)     //���ý����õĹ����������ַ������б���
{
    int c,p,i;
    char cd[N+1];
    int start;
    for(i=1; i<k; i++)
    {
        hc[i].data = ht[i].data;
        p=ht[i].parent;
        c=i;
        start=0;
        while(p!=0)
        {
            if(ht[p].lchild==c)
                    cd[start++]='0';
            else if(ht[p].mchild==c)
                 cd[start++]='1';
            else cd[start++]='2';
            c=p;
            p=ht[p].parent;
        }
        cd[start]='\0';
        strcpy(hc[i].bits,cd);
    }
    printf("\n\nÿ���ַ���Ӧ�ı���Ϊ:\n");
    for(i=1; i<k; i++)
        printf("<%d   %c  %s>  \n",i,hc[i].data,hc[i].bits);
}

void WriteToFile(HuffmanCode hc,int n)   //���������洢���ļ��ļ�ywq2.txt��
{
    FILE *fp1,*fp2;
    char ch;
    int i;
    if((fp1=fopen("D://pad1.txt","r"))==NULL)
    {
        printf("\n�ļ�������!");
        exit(1);
    }
    if((fp2=fopen("d://pad2.txt","w"))==NULL)
    {
        printf("\n�ļ�������!");
        exit(1);
    }
    ch = fgetc(fp1);
    printf("\n������Ϊ��");
    while(ch != EOF)
    {
        for(i=1; i<n; i++)
            if(ch == hc[i].data)
            {
                fputs(hc[i].bits,fp2);
                printf("%s",hc[i].bits);
            }
        ch = fgetc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
    printf("\n");
}




void main()
{
    int i,k;
    int j=1;
    HuffmanTree ht;
    HuffmanCode hc;
    str s2[128];
    printf("\n-------------------------------����������������---------------------------------");
    printf("�ļ�Ӧ����d�̣�������Ϊpad1.txt");
    k=read(s2);
    getchar();
    CrtHuffmanTree(ht,s2,&k);
    CrtHuffmanCode(ht,hc,k);
    WriteToFile(hc,k);
    getchar();
    printf("\n\n");
    printf("�����Ĺ�������Ϊ:");
    printf("\nnumber\tdata\tweight\tlchild\tmchild\trchild\tparent ");
    for(i=1; ht[i].parent!=0; i++)
    {
        printf("\n%d :     %c        %d        %d       %d       %d        %d",i,ht[i].data,ht[i].weight,ht[i].lchild,ht[i].mchild,ht[i].rchild,ht[i].parent) ;
    }
    printf("\n\n");
    getchar();
    //printf("\n\n��������˳�...\n");
}
