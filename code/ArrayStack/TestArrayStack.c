# include <stdio.h>
# include "ArrayStack.h"

Status visit(Elemtype * p);

int main(void)
{
	ArrayStack S;
	int len;
	int e;

	InitStack(&S);
	printf("Please input the length of stack:");
	scanf("%d", &len);
	printf("Please input the data of Elem:\n");
	for (int i=0; i<len; ++i)
	{
		scanf("%d", &e);
		Push(&S, e);
	}
	printf("The data of Stack:\n");
	StackTraverse(S, visit);
	printf("\n");
	GetTop(S, &e);
	printf("The top element is %d", e);

	return 0;
}

Status visit(Elemtype * p)
{
	if (!*p)
		return ERROR;
	printf("%d ", *p);
	return OK;
}
