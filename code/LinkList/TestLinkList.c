#include <stdio.h>
#include "LinkList.h"

Status visit(ElemType * pe);
LinkList ElemInput();

int main() {
    ElemType e;
    int i;

    printf("-----Creating List-----\n");
    LinkList L = ElemInput();
    printf("The length of list is %d\n", ListLength(L));
    printf("The element of list:\n");
    ListTraverse(L, visit);
    printf("\n");

    printf("--------Location-------\n");
    printf("Input element:");
    scanf("%d", &e);
    int count = LocateElem(L, e, equal);
    if (count == 0)
        printf("The element doesn't exist!\n");
    else
        printf("The location of element is %d\n", count);
    printf("\n");

    printf("---------Insert--------\n");
    printf("Inserted element:");
    scanf("%d", &e);
    printf("Inserted location:");
    scanf("%d", &i);
    if ( ListInsert(&L, i, e) )
    {
        printf("Insertion complete!\n");
        printf("The element of list:\n");
        ListTraverse(L, visit);
        printf("\n");
    }
    else
        printf("Insertion fail!\n");
    printf("\n");

    printf("--------Deletion-------\n");
    Link q = Remove(&L);
    printf("The Deleted element is %d\n", q->data);
    printf("The element of list:\n");
    ListTraverse(L, visit);
    printf("\n");
}

Status visit(ElemType * pe)
{
    if (!*pe)
        return ERROR;
    printf("%d ", *pe);
    return OK;
}

LinkList ElemInput()
{
    LinkList L = InitList();
    ElemType e;
    int n;
    printf("Input the length of List:\n");
    scanf("%d", &n);
    printf("Input the element of list:\n");
    for (int i=1; i<=n; ++i)
    {
        scanf("%d", &e);
        Link s = MakeNode(e);
        Append(&L, s);
    }
    return L;
}