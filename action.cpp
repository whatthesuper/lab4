#include<stdio.h>
#include<stdlib.h>


typedef struct TREE
{
    char data;
    TREE *lchild;
    TREE *rchild;
}*tree;

struct celltype
{
    tree data;
    celltype *next;
};

struct queue
{
    celltype *front;
    celltype *rear;
};
tree creat(tree b);
int isempty(tree b);
void preorder(tree b);
void postorder(tree b);
void inorder(tree b);
int main()
{
    tree t;
    printf("先序建立：\n请输入节点的数据，输入‘#’表示空。\n");
    t=creat(t);
    printf("前序遍历：");
    preorder(t);
    printf("\n后续遍历：");
    postorder(t);
    printf("\n中序遍历：");
    inorder(t);
    return 0;
}

tree creat(tree b)
{
    char x;
    tree p;
    scanf(" %c",&x);
    if(x=='#')
    {
        return NULL;
    }
    else
    {
        p=(struct TREE *)malloc(sizeof(struct TREE));
        b=p;
        b->data=x;
        b->lchild=creat(b->lchild);
        b->rchild=creat(b->rchild);
    }
    return b;
}

int isempty(tree b)
{
    if(b!=NULL)
    return 0;
    else
    return 1;
}
void preorder(tree b)
{
    if(!isempty(b))
    {
        printf("%c",b->data);
        preorder(b->lchild);
        preorder(b->rchild);
    }
}
void inorder(tree b)
{
    if(!isempty(b))
    {
        preorder(b->lchild);
        printf("%c",b->data);
        preorder(b->rchild);
    }
}
void postorder(tree b)
{
    if(!isempty(b))
    {
        postorder(b->lchild);
        printf("%c",b->data);
        postorder(b->rchild);
    }
}
