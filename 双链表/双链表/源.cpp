#include <stdio.h>
#include <malloc.h>
typedef int ElemType;
typedef struct DNode		//定义双链表结点类型
{
	ElemType data;
	struct DNode* prior;	//指向前驱结点
	struct DNode* next;		//指向后继结点
} DLinkNode;
void CreateListF(DLinkNode*& L, ElemType a[], int n)
//头插法建双链表
{
	DLinkNode* s;
	L = (DLinkNode*)malloc(sizeof(DLinkNode));  	//创建头结点
	L->prior = L->next = NULL;
	for (int i = 0; i < n; i++)
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));//创建新结点
		s->data = a[i];
		s->next = L->next;			//将结点s插在原开始结点之前,头结点之后
		if (L->next != NULL)
			L->next->prior = s;
		L->next = s;
		s->prior = L;
	}
}
void CreateListR(DLinkNode*& L, ElemType a[], int n)
//尾插法建双链表
{
	DLinkNode* s, * r;
	L = (DLinkNode*)malloc(sizeof(DLinkNode));  	//创建头结点
	L->prior = L->next = NULL;
	r = L;					//r始终指向终端结点,开始时指向头结点
	for (int i = 0; i < n; i++)
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));//创建新结点
		s->data = a[i];
		r->next = s; s->prior = r;	//将结点s插入结点r之后
		r = s;
	}
	r->next = NULL;				//尾结点next域置为NULL
}
void InitList(DLinkNode*& L)
{
	L = (DLinkNode*)malloc(sizeof(DLinkNode));  	//创建头结点
	L->prior = L->next = NULL;
}
void DestroyList(DLinkNode*& L)
{
	DLinkNode* pre = L, * p = pre->next;
	while (p != NULL)
	{
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);
}
bool ListEmpty(DLinkNode* L)
{
	return(L->next == NULL);
}
int ListLength(DLinkNode* L)
{
	DLinkNode* p = L;
	int i = 0;
	while (p->next != NULL)
	{
		i++;
		p = p->next;
	}
	return(i);
}
void DispList(DLinkNode* L)
{
	DLinkNode* p = L->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
bool GetElem(DLinkNode* L, int i, ElemType& e)
{
	int j = 0;
	DLinkNode* p = L;
	if (i <= 0)
		return false;		//i错误返回假
	while (j < i && p != NULL)
	{
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else
	{
		e = p->data;
		return true;
	}
}
int LocateElem(DLinkNode* L, ElemType e)
{
	int n = 1;
	DLinkNode* p = L->next;
	while (p != NULL && p->data != e)
	{
		n++;
		p = p->next;
	}
	if (p == NULL)
		return(0);
	else
		return(n);
}
bool ListInsert(DLinkNode*& L, int i, ElemType e)
{
	int j = 0;
	DLinkNode* p = L, * s;
	if (i <= 0)
		return false;		//i错误返回假
	while (j < i - 1 && p != NULL)
	{
		j++;
		p = p->next;
	}
	if (p == NULL)				//未找到第i-1个结点
		return false;
	else						//找到第i-1个结点p
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));	//创建新结点s
		s->data = e;
		s->next = p->next;		//将结点s插入到结点p之后
		if (p->next != NULL)
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}
bool ListDelete(DLinkNode*& L, int i, ElemType& e)
{
	int j = 0;
	DLinkNode* p = L, * q;
	if (i <= 0)
		return false;		//i错误返回假
	while (j < i - 1 && p != NULL)
	{
		j++;
		p = p->next;
	}
	if (p == NULL)				//未找到第i-1个结点
		return false;
	else						//找到第i-1个结点p
	{
		q = p->next;				//q指向要删除的结点
		if (q == NULL)
			return false;		//不存在第i个结点
		e = q->data;
		p->next = q->next;		//从单链表中删除*q结点
		if (p->next != NULL) p->next->prior = p;
		free(q);				//释放q结点
		return true;
	}
}
int main()
{
	DLinkNode* L;
	ElemType e;
	ElemType a[] = { 1,2,3,4 };
	CreateListF(L, a, 4);        //尾插法建立链表 
	printf("尾插法所得顺序为: ");
	DispList(L);
	DestroyList(L);
	CreateListR(L, a, 4);        //头插法建立链表 
	printf("头插法所得顺序为：");
	DispList(L);
	printf("链表的长度为:%d\n", ListLength(L));
	ListInsert(L, 4, 5);          //在链表第四个元素前插入5 
	printf("插入一个元素后链表的元素为:");
	DispList(L);
	ListDelete(L, 1, e);          //删除链表中第一个元素，并将它的值赋给e 
	printf("删除的元素为:%d\n", e);
	printf("删除一个元素后链表的元素为:");
	DispList(L);
	printf("当前链表是否为空:%d\n", ListEmpty(L));
	GetElem(L, 1, e);
	printf("链表第一个元素为:%d\n", e);
	printf("值为2的元素在链表中的位置为:%d\n", LocateElem(L, 2));
	return 0;
}

