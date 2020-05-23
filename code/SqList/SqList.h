# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

//定义函数状态代码
#define	TRUE	1
#define	FALSE	0
#define	OK	1
#define	ERROR	0
#define	INFEASIBLE	-1
#define	OVERFLOW	-2

//ElemType是数据类型别名，在此为int类型别名，也可为浮点数类型
//Status是函数的类型，其值是函数结果状态代码
typedef int ElemType;
typedef int Status;

//-----线性表的动态分配顺序存储结构-----
#define	LIST_INIT_SIZE	100 //初始分配量
#define	LISTINCREMENT	10  //分配增量
typedef struct
{
	ElemType * elem; //存储空间基址
	int length;      //当前长度
	int listsize;    //分配的存储容量，单位为sizeof(ElemType)
}SqList;

//构造一个空的顺序线性表
Status InitList(SqList * pL);

//销毁顺序线性表L
Status DestroyList(SqList * pL);

//将L重置为空表
Status CleanList(SqList * pL);

//若L为空表，则返回TRUE，否则返回FALSE
Status ListEmpty(SqList L);

//返回L中数据元素个数
int ListLength(SqList L);

//用e返回L中第i个数据元素的值
Status GetElem(SqList L, int i, ElemType * e);

//比较两数是否相等
Status equal(ElemType a, ElemType b);

//返回L中第1个与e满足关系compare()的数据元素的位序，若这样的数据元素不存在，则返回值为0
//Status(*compare)(ElemType, ElemType)定义了一个函数指针，用与指向该函数
//(*compare)(*p++, e)用该函数指针调用该函数
int LocateElem(SqList L, ElemType e, Status(*compare)(ElemType, ElemType));

//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
Status PriorElem(SqList L, ElemType cur_e, ElemType * pre_e);

//若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义
Status NextElem(SqList L, ElemType cur_e, ElemType * next_e);

//在L中第i个位置之前插入新的数据元素e，L的长度加1
Status ListInsert(SqList * pL, int i, ElemType e);

//删除L的第i个数据元素，并用e返回其值，L的长度减1
Status ListDelete(SqList * pL, int i, ElemType * pe);

//依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
Status ListTraverse(SqList L, Status(*visit)(ElemType *));

//将所有在线性表Lb中但不在La中的数据元素插到La中
void union_Sq(SqList * pLa, SqList Lb);

//已知线性表La和Lb中的数据元素按值递增排列
//归并La和Lb得到新的线性表Lc，Lc的数据元素也按值递增排序
void MergeList(SqList La, SqList Lb, SqList * pLc);

//在线性表末尾的位置添加元素
Status ListAppend(SqList * pL, ElemType e);