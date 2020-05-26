#include "ArrayList.h"

//构造一个空的顺序线性表
Status InitList(ArrayList * pL)
{
    pL->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (! pL->elem)
        exit(OVERFLOW); //存储分配失败
    pL->length = 0;
    pL->listsize = LIST_INIT_SIZE;
    return OK;
}

//销毁顺序线性表L
Status DestroyList(ArrayList * pL)
{
    free(pL->elem);
    pL->elem = NULL;
    pL->length = 0;
    pL->listsize = 0;
    return OK;
}

//将L重置为空表
Status CleanList(ArrayList * pL)
{
    pL->length = 0;
    return OK;
}

//若L为空表，则返回TRUE，否则返回FALSE
Status ListEmpty(ArrayList L)
{
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

//返回L中数据元素个数
int ListLength(ArrayList L)
{
    return L.length;
}

//用e返回L中第i个数据元素的值
Status GetElem(ArrayList L, int i, ElemType * e)
{
    if (i<1 || i>L.length)
        exit(ERROR);
    *e = L.elem[i-1];
    return OK;
}

//比较两数是否相等
Status equal(ElemType a, ElemType b)
{
    if (a == b)
        return 1;
    else
        return 0;
}

//返回L中第1个与e满足关系compare()的数据元素的位序，若这样的数据元素不存在，则返回值为0
//Status(*compare)(ElemType, ElemType)定义了一个函数指针，用与指向该函数
//(*compare)(*p++, e)用该函数指针调用该函数
int LocateElem(ArrayList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
    ElemType * p;
    int i = 1;
    p = L.elem;
    while (i<=L.length && !(*compare)(*p++, e))
        ++i;
    if (i<=L.length)
        return i;
    else
        return 0;
}

//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
Status PriorElem(ArrayList L, ElemType cur_e, ElemType * pre_e)
{
    int i = 2;
    ElemType * p = L.elem + 1;
    while (i<=L.length && *p!=cur_e)
    {
        p++;
        i++;
    }
    if (i<=L.length)
    {
        *pre_e = *--p;
        return OK;
    }
    else
        return INFEASIBLE;
}

//若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义
Status NextElem(ArrayList L, ElemType cur_e, ElemType * next_e)
{
    int i = 1;
    ElemType * p = L.elem;
    while (i<L.length && *p!=cur_e)
    {
        p++;
        i++;
    }
    if (i == L.length)
        return INFEASIBLE;
    else
    {
        *next_e = *++p;
        return OK;
    }
}

//在L中第i个位置之前插入新的数据元素e，L的长度加1
Status ListInsert(ArrayList * pL, int i, ElemType e)
{
    ElemType * newbase, *p, *q;
    if (i<1 || i>pL->length)
        return ERROR;
    if (pL->length >= pL->listsize)
    {
        newbase = (ElemType *)realloc(pL->elem, (pL->listsize+LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);
        pL->elem = newbase;
        pL->listsize += LISTINCREMENT;
    }
    q = pL->elem + i -1;
    for (p=pL->elem+pL->length-1; p>=q; --p)
        *(p + 1) = *p;
    *q = e;
    ++(pL->length);
    return OK;
}

//删除L的第i个数据元素，并用e返回其值，L的长度减1
Status ListDelete(ArrayList * pL, int i, ElemType * pe)
{
    if (i<1 || i>pL->length)
        return ERROR;
    ElemType * p, *q;
    p = pL->elem + i - 1;
    *pe = *p;
    q = pL->elem + pL->length -1;
    for (++p; p<=q; ++p)
        *(p - 1) = *p;
    --pL->length;
    return OK;
}

//依次对L的每个数据元素调用函数visit()，一旦visit()失败，则操作失败
Status ListTraverse(ArrayList L, Status(*visit)(ElemType *))
{
    ElemType * p;
    p = L.elem;
    for (int i=1; i<=L.length; ++i)
        if( !visit(p++) )
            return ERROR;
    return OK;
}

//将所有在线性表Lb中但不在La中的数据元素插到La中
void union_Sq(ArrayList * pLa, ArrayList Lb)
{
    int La_len;
    int Lb_len;
    La_len = ListLength(*pLa);
    Lb_len = ListLength(Lb);
    ElemType e;
    for (int i=1; i<=Lb_len; i++)
    {
        GetElem(Lb, i, &e);
        if ( !LocateElem(*pLa, e, equal) )
        {
            ++pLa->length;
            ListInsert(pLa, ++La_len, e);
        }
    }
}

//已知线性表La和Lb中的数据元素按值递增排列
//归并La和Lb得到新的线性表Lc，Lc的数据元素也按值递增排序
void MergeList(ArrayList La, ArrayList Lb, ArrayList * pLc)
{
    ElemType * pa, * pb, * pa_last, * pb_last, * pc;
    pa = La.elem;
    pb = Lb.elem;
    pLc->listsize = pLc->length = La.length + Lb.length;
    pc = pLc->elem = (ElemType *)malloc(sizeof(ElemType) * pLc->listsize);
    if (!pLc->elem)
        exit(OVERFLOW);
    pa_last = La.elem + La.length - 1;
    pb_last = Lb.elem + Lb.length - 1;
    while (pa<=pa_last && pb<=pb_last)
    {
        if (*pa<*pb)
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }
    while (pa<=pa_last)
        *pc++ = *pa++;
    while (pb<=pb_last)
        *pc++ = *pb++;
}

//补充追加函数ListAppend(),在线性表末尾的位置添加元素
Status ListAppend(ArrayList * pL, ElemType e)
{
    ElemType * newbase , * p;
    if (pL->length>=pL->listsize)
    {
        newbase = (ElemType *)realloc(pL->elem, (pL->listsize+LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);
        pL->elem = newbase;
        pL->length += LISTINCREMENT;
    }
    p = pL->elem + pL->length;
    *p = e;
    ++(pL->length);
    return OK;
}
