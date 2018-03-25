#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode* parent;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

TreeNode* CreatNode(char value)
{
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->parent = NULL;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

TreeNode* _CreatTree(char arr[],int size,int* index,TreeNode** prev,char invalid)
{
    if(arr == NULL || index == NULL || prev == NULL)
    {
        return NULL;
    }
    if(*index >= size)
    {
        return NULL;
    }
    if(arr[*index] == invalid)
    {
        return NULL;
    }
    TreeNode* root = CreatNode(arr[*index]);
    root->parent = *prev;
    *prev = root;
    ++(*index);
    root->lchild = _CreatTree(arr,size,index,prev,invalid);
    *prev = root;
    ++(*index);
    root->rchild = _CreatTree(arr,size,index,prev,invalid);
    return root;
}

TreeNode* CreatTree(char arr[],int size,char invalid)
{
    if(arr == NULL)
    {
        return NULL;
    }
    if(size <= 0)
    {
        return NULL;
    }
    int index = 0;
    TreeNode* prev = NULL;
    return _CreatTree(arr,size,&index,&prev,invalid);
}

void PreOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%c ",root->data);
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
    printf("%c ",root->data);
    InOrder(root->rchild);
}

TreeNode* Find_Next_Node(TreeNode* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    //1.如果这个节点有右子树，那么他的下一个节点就是右子树的最左侧节点
    if(node->rchild != NULL)
    {
        TreeNode* cur = node->rchild;
        while(cur->lchild != NULL)
        {
            cur = cur->lchild;
        }
        return cur;
    }
    //2.如果这个节点没有右子树，那么他的下一个节点是自身作为左子树的父节点
    else
    {
        TreeNode* child = node;
        TreeNode* parent = node->parent;
        while(parent != NULL)
        {
            if(parent->lchild == child)
            {
                return parent;
            }
            child = parent;
            parent = parent->parent;
        }
    }
    return NULL;
}

int main()
{
    char arr[] = "abd##eh##i##cf##g##";
    int size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreatTree(arr,size,'#');
    printf("先序 ：");
    PreOrder(root);
    printf("\n");
    printf("中序 ：");
    InOrder(root);
    printf("\n");

    TreeNode* next_node = Find_Next_Node(root->lchild->lchild);
    printf("d next node ecxept b,%p ;actual %c,%p\n",root->lchild,next_node->data,next_node);

    next_node = Find_Next_Node(root->lchild->rchild->lchild);
    printf("h next node ecxept e,%p ;actual %c,%p\n",root->lchild->rchild,next_node->data,next_node);

    next_node = Find_Next_Node(root->lchild->rchild->rchild);
    printf("i next node ecxept a,%p ;actual %c,%p\n",root,next_node->data,next_node);

    next_node = Find_Next_Node(root->rchild->rchild);
    printf("g next node ecxept null ;actual %p\n",next_node);
//    printf("a parent %p\n",root->parent);
//    printf("b parent %c\n",root->lchild->parent->data);
//    printf("d parent %c\n",root->lchild->lchild->parent->data);
//    printf("e parent %c\n",root->lchild->rchild->parent->data);
//    printf("c parent %c\n",root->rchild->parent->data);
//    printf("i parent %c\n",root->lchild->rchild->rchild->parent->data);
//    printf("g parent %c\n",root->rchild->rchild->parent->data);
    return 0;
}
