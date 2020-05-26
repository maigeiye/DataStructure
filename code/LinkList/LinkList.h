# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

//定义函数状态代码
#define TRUE    1
#define FALSE   0
#define OK  1
#define ERROR   0
#define INFEASIBLE  
#define OVERFLOW    -2

//ElemType是数据类型别名，在此为int类型别名，也可为浮点数类型
//Status是函数的类型，其值是函数结果状态代码
typedef int ElemType;
typedef int Status;

//-----线性表的单链表存储结构------
typedef struct LNode
{
    ElemType data;
    struct LNode * next;
} * Link, * Position;

typedef struct
{
    Link head, tail;
    int len;
}LinkList;

Link MakeNode(ElemType e);

void FreeNode(Link p);

LinkList InitList();

Status ClearList(LinkList * L);

Status DestroyList(LinkList * L);

//已知h指向线性链表的头结点，将s所指结点插入到第一个结点之前
Status InsFirst(LinkList * L, Link h, Link s);

//已知h指向线性链表的头结点，删除链表中的第一个结点并返回
Link DelFirst(LinkList * L, Link h);

//将指针s所指（彼此以指针相链）的一串结点链接在线性链表L的最后一个结点之后，并改变链表L的尾指针指向新的尾结点
Status Append(LinkList * L, Link s);

//删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
Link Remove(LinkList * L);

//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前
void InsBefore(LinkList * L, Link p, Link s);
    
//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后
void InsAfter(LinkList * L, Link p, Link s);

//已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
void SetCurElem(Link p, ElemType e);

//已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
ElemType GetCurElem(Link p);

Status ListEmpty(LinkList L);

int ListLength(LinkList L);

Position GetHead(LinkList L);

Position GetLast(LinkList L);

Position PriorPos(LinkList L, Link p);

Position NextPos(LinkList L, Link p);

//返回线性链表L中第i个结点的位置，i值不合法时返回ERROR
Status LocatePos(LinkList L, int i, Link * q);

//比较两数是否相等
Status equal(ElemType a, ElemType b);

//返回线性链表L中第1个与e满足函数compare()判定关系的元素的位置，若不存在，返回ERROR
int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType));

//依次对L的每个元素调用函数visit()，一旦visit()失败，则操作失败
Status ListTraverse(LinkList L, Status (*visit)(ElemType *));

//在头结点的单链线性表L的第i个元素之前插入元素e
Status ListInsert(LinkList * L, int i, ElemType e);

//已知单链线性表La和Lb的元素按值非递减排列
//归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
Status MergeList(LinkList * La, LinkList * Lb, LinkList * Lc, int (*compare)(ElemType, ElemType));

