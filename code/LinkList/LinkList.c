#include "LinkList.h"

Link MakeNode(ElemType e)
{
	Link p = (Link)malloc(sizeof(Link));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	return p;
}

void FreeNode(Link p)
{
	free(p);
	p = NULL;
}

LinkList InitList()
{
	LinkList L;
	Link p = (Link)malloc(sizeof(struct LNode));
	if (!p)
		exit(OVERFLOW);
	p->next = NULL;
	L.head = L.tail = p;
	L.len = 0;
	return L;
}

Status ClearList(LinkList * L)
{
	Link p, q;
	p = L->head->next;
	
	while (p->next)
	{
		q = p->next;
		free(p);
		p = NULL;
		p = q;
	}
	L->head->next = NULL;
	L->tail = L->head;
	L->len = 0;
	return OK;
}

Status DestroyList(LinkList * L)
{
	ClearList(L);
	free(L->head);
	L->head = L->tail = NULL;
	return OK;
}

//已知h指向线性链表的头结点，将s所指结点插入到第一个结点之前
Status InsFirst(LinkList * L, Link h, Link s)
{
	if (h && s)
	{
		s->next = h->next;
		h->next = s;
		++L->len;
		return OK;
	}
	return ERROR;
}

//已知h指向线性链表的头结点，删除链表中的第一个结点并返回
Link DelFirst(LinkList * L, Link h)
{
	Link q = h->next;
	if (!q)
		return ERROR;
	h->next = q->next;
	q->next = NULL;
	if (!h->next)		//h后只有一个结点,需要重置尾结点
		L->tail = h;
	--L->len;
	return q;
}

//将指针s所指（彼此以指针相链）的一串结点链接在线性链表L的最后一个结点之后，并改变链表L的尾指针指向新的尾结点
Status Append(LinkList * L, Link s)
{
		int count = 0;
		L->tail->next = s;
		while(s)
		{
			L->tail = s;
			s = s->next;
			count++;
		}
		L->len += count;
		return OK;
}

//删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
Link Remove(LinkList * L)
{
	Link q;
	if (!L->len)
	{
		q = NULL;
		return ERROR;
	}
	q = L->tail;
	Link p = L->head;
	while (p->next != L->tail)	//寻找尾结点的前驱
		p = p->next;
	p->next = NULL;
	L->tail = p;
	--L->len;
	return q;
}

//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前
void InsBefore(LinkList * L, Link p, Link s)
{
	Link q;
	q = L->head;
	while(q->next != p)
		q = q->next;
	s->next = q->next;
	q->next = s;
	++L->len;
}
	
//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后
void InsAfter(LinkList * L, Link p, Link s)
{
	if (p == L->tail)	//若p指向尾结点，尾指针需要重置
		L->tail = s;
	s->next = p->next;
	p->next = s;
	++L->len;
}

//已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
void SetCurElem(Link p, ElemType e)
{
	p->data = e;
}

//已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
ElemType GetCurElem(Link p)
{
	return p->data;
}

Status ListEmpty(LinkList L)
{
	if (L.len)
		return TRUE;
	else
		return FALSE;
}

int ListLength(LinkList L)
{
	return L.len;
}

Position GetHead(LinkList L)
{
	return L.head;
}

Position GetLast(LinkList L)
{
	return L.tail;
}

Position PriorPos(LinkList L, Link p)
{
	Link q = L.head->next;
	if (q==p)		//该结点是首结点，无前驱
		return NULL;
	else
	{
		while(q->next == p)
			q = q->next;
		return q;
	}
}

Position NextPos(LinkList L, Link p)
{
	return p->next;
}

//用q返回线性链表L中第i个结点的位置，i值不合法时返回ERROR
Status LocatePos(LinkList L, int i, Link * q)
{
	Link p;
	int count = 0;
	p = L.head;
	if (i<0 || i>L.len)
		return ERROR;
	while (count<i)
	{
		p = p->next;
		++count;
	}
	*q = p;
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

//返回线性链表L中第1个与e满足函数compare()判定关系的元素的位置，若不存在，返回ERROR
int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	Link p = L.head->next;
	int count = 1;
	while (p && !(*compare)(p->data, e))
	{
		p = p->next;
		count++;
	}
	if (p)
		return count;
	else
		return ERROR;
}

//依次对L的每个元素调用函数visit()，一旦visit()失败，则操作失败
Status ListTraverse(LinkList L, Status (*visit)(ElemType *))
{
	Link p = L.head->next;
	while (p)
	{
		if (!visit(&(p->data)))
			return ERROR;
		p = p->next;
	}
	return OK;
}

//在头结点的单链线性表L的第i个元素之前插入元素e
Status ListInsert(LinkList * L, int i, ElemType e)
{
	Link q;
	// i值不合法
	 if (!LocatePos(*L, i, &q))
	 	return ERROR;
	Link p = MakeNode(e);
	InsBefore(L, q, p);
	return OK;
}

//已知单链线性表La和Lb的元素按值非递减排列
//归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
Status MergeList(LinkList * La, LinkList * Lb, LinkList * Lc, int (*compare)(ElemType, ElemType))
{
	return OK;
}

