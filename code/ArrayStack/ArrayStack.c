#include "ArrayStack.h"

//构造一个空栈
Status InitStack(ArrayStack * pS)
{
    pS->base = (Elemtype *)malloc(STACK_INIT_SIZE * sizeof(Elemtype));
    if (!pS->base)
        exit(OVERFLOW);
    pS->top = pS->base;
    pS->stacksize = STACK_INIT_SIZE;
    return OK;
}

//销毁栈
Status DestoryStack(ArrayStack * pS)
{
    free(pS->base);
    pS->base = NULL;
    pS->top = NULL;
    pS->stacksize = 0;
    return OK;
}

//把栈重置为空栈
Status ClearStack(ArrayStack * pS)
{
    pS->top = pS->base;
    return OK;
}

//若栈为空栈，返回TURE，否则返回FALSE
Status StackEmpty(ArrayStack S)
{
    if(S.top == S.base)
        return TRUE;
    else
        return FALSE;
}

//返回栈的元素个数
int StackLength(ArrayStack S)
{
    return S.top - S.base;
}

//若栈不为空，则用e返回栈的栈顶元素，并返回OK，否则返回ERROR
Status GetTop(ArrayStack S, Elemtype * pe)
{
    if (S.top == S.base)
        return ERROR;
    *pe = *(S.top - 1);
    return OK;
}

//插入元素e为栈顶元素
Status Push(ArrayStack * pS, Elemtype e)
{
    if (pS->top - pS->base >= pS->stacksize)
    {
        pS->base = (Elemtype *)realloc(pS->base, (pS->stacksize + STACKINCREMENT) * sizeof(Elemtype));
        if (! pS->base)
            exit(OVERFLOW);
        pS->stacksize += STACKINCREMENT;
    }
    *pS->top++ = e;
    return OK;
}

//若栈不空，则删除栈的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
Status Pop(ArrayStack * pS, Elemtype * pe)
{
    if (pS->top == pS->base)
        return ERROR;
    *pe = *--pS->top;
    return OK;
}

//从栈底到栈顶依次对栈中的每个元素调用函数visit()。一旦visit()失败，则操作失败
Status StackTraverse(ArrayStack S, Status(* visit)(Elemtype *))
{
    Elemtype * p;
    p = S.base;
    while (p != S.top)
    {
        if ( !(*visit)(p) )
            return ERROR;
        ++p;
    }
    return OK;
}
