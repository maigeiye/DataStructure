#include <stdio.h>
#include <malloc.h>

//定义函数状态代码
#define TRUE    1
#define FALSE   0
#define OK  1
#define ERROR   0
#define INFEASIBLE  
#define OVERFLOW    -2

typedef int TElemType;
typedef int Status;

//-----链式二叉树的存储结构-----
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode * pLchild;
    struct BiTNode * pRchild;
}BiTNode, * BiTree

BiTree CreateBiTree();