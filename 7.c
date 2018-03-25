#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

TreeNode* CreateNode(int value)
{
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

int FindPos(int value,int In[],int beg,int end)
{
    if(In == NULL)
    {
        return -1;
    }
    if(end - beg <= 0)
    {
        return -1;
    }
    int i = beg;
    for(; i < end; ++i)
    {
        if(In[i] == value)
        {
            return i;
        }
    }
    return -1;
}

TreeNode* _ReBulidTree(int Pre[],int In[],int pre_size,int beg,int end,int* index)
{
    if(Pre == NULL || In == NULL || index == NULL)
    {
        return NULL;
    }
    if(*index >= pre_size)
    {
        return NULL;
    }
    if(end - beg <= 0)
    {
        return NULL;
    }
    TreeNode* root = CreateNode(Pre[*index]);
    int pos = FindPos(Pre[*index],In,beg,end);
    if(pos == -1)
    {
        printf("数据有误...\n");
        exit(1);
    }
    ++(*index);
    root->lchild = _ReBulidTree(Pre,In,pre_size,beg,pos,index);
    root->rchild = _ReBulidTree(Pre,In,pre_size,pos + 1,end,index);
    return root;
}

TreeNode* ReBuildTree(int Pre[],int pre_size,int In[],int in_size)
{
    if(Pre == NULL || In == NULL)
    {
        return NULL;
    }
    if(pre_size != in_size || pre_size <= 0)
    {
        return NULL;
    }
    int index = 0;
    return _ReBulidTree(Pre,In,pre_size,0,in_size,&index);
}

void PreOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%d ",root->data);
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}

void InOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    InOrder(root->lchild);
    printf("%d ",root->data);
    InOrder(root->rchild);
}

int main()
{
//    int Pre[] = {1,2,4,7,3,5,6,8};
//    int In[] = {4,7,2,1,5,3,8,6};

//    int Pre[] = {1,2,3,4,5};
//    int In[] = {5,4,3,2,1};

//    int Pre[] = {1,2,3,4,5};
//    int In[] = {1,2,3,4,5};

//    int Pre[] = {1,2,4,5,3,6,7};
//    int In[] = {4,2,5,1,6,3,7};

//    int Pre[] = {};
//    int In[] = {};

    int Pre[] = {1,2,4,5,3,6,7};
    int In[] = {1,2,3,4,5,6,7};
    int pre_size = sizeof(Pre)/sizeof(Pre[0]);
    int in_size = sizeof(In)/sizeof(In[0]);
    TreeNode* root = ReBuildTree(Pre,pre_size,In,in_size);
    printf("先序 ：");
    PreOrder(root);
    printf("\n");
    printf("中序 ：");
    InOrder(root);
    printf("\n");
    return 0;
}
