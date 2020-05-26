# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

#define	TRUE	1
#define	FALSE	0
#define	OK	1
#define	ERROR	0
#define	INFEASIBLE	
#define	OVERFLOW	-2

typedef int Elemtype;
typedef int Status;

#define	STACK_INIT_SIZE	100
#define STACKINCREMENT	10
typedef struct
{
	Elemtype * base;//栈底指针
	Elemtype * top;//栈顶指针
	int stacksize;
}ArrayStack;

//构造一个空栈
Status InitStack(ArrayStack * pS);

//销毁栈
Status DestoryStack(ArrayStack * pS);

//把栈重置为空栈
Status ClearStack(ArrayStack * pS);

//若栈为空栈，返回TURE，否则返回FALSE
Status StackEmpty(ArrayStack S);

//返回栈的元素个数
int StackLength(ArrayStack S);

//若栈不为空，则用e返回栈的栈顶元素，并返回OK，否则返回ERROR
Status GetTop(ArrayStack S, Elemtype * pe);

//插入元素e为栈顶元素
Status Push(ArrayStack * pS, Elemtype e);

//若栈不空，则删除栈的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
Status Pop(ArrayStack * pS, Elemtype * pe);

//从栈底到栈顶依次对栈中的每个元素调用函数visit()。一旦visit()失败，则操作失败
Status StackTraverse(ArrayStack S, Status(* visit)(Elemtype *));