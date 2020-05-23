# include <stdio.h>
# include "SqList.h"

Status visit(ElemType * pe);
void ElemInput(SqList * pL);

int main(void)
{
	SqList L;
	ElemType e;
	int i;

	printf("-----Creating List-----\n");
	ElemInput(&L);
	printf("The length of list is %d\n", ListLength(L));
	ListTraverse(L, visit);
	printf("\n");
	printf("\n");


	printf("--------Location-------\n");
	printf("Input element:");
	scanf("%d", &e);
	i = LocateElem(L, e, equal);
	if (i == 0)
		printf("The element doesn't exist!\n");
	else
		printf("The location of element is %d\n", i);
	printf("\n");

	printf("---------Insert--------\n");
	printf("Inserted element:");
	scanf("%d", &e);
	printf("Inserted location:");
	scanf("%d", &i);
	if ( ListInsert(&L, i, e) )
	{
		printf("Insertion complete!\n");
		ListTraverse(L, visit);
		printf("\n");
	}
	else
		printf("Insertion fail!\n");
	printf("\n");

	printf("--------Deletion-------\n");
	printf("Deleted location:");
	scanf("%d", &i);
	if (ListDelete(&L, i, &e))
		printf("Deleted element is %d\n", e);
	else
		printf("Out of range!\n");
	printf("\n");

	printf("---------Union---------\n");
	SqList La, Lb;
	printf("Create List La\n");
	ElemInput(&La);
	printf("Create List Lb\n");
	ElemInput(&Lb);
	union_Sq(&La, Lb);
	printf("After uniting\n");
	ListTraverse(La, visit);
	printf("\n");
	printf("\n");

	printf("-------Merge List------\n");
	printf("Create List La\n");
	ElemInput(&La);
	printf("Create List Lb\n");
	ElemInput(&Lb);
	SqList Lc;
	MergeList(La, Lb, &Lc);
	printf("After merging\n");
	ListTraverse(Lc, visit);
	printf("\n");
	return 0;
}

Status visit(ElemType * pe)
{
	if (!*pe)
		return ERROR;
	printf("%d ", *pe);
	return OK;
}

//补充创造线性表并输入元素的函数
void ElemInput(SqList * pL)
{
	ElemType e;
	int n;
	InitList(pL);
	printf("Input the length of List:\n");
	scanf("%d", &n);
	printf("Input the element of list:\n");
	for (int i=1; i<=n; ++i)
	{
		scanf("%d", &e);
		ListAppend(pL, e);
	}
}

