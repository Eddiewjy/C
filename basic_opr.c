#include <io.h>      /* eof() */
#include <limits.h>  /* INT_MAX等 */
#include <malloc.h>  /* malloc()等 */
#include <math.h>    /* floor(),ceil(),abs() */
#include <process.h> /* exit() */
#include <stdio.h>   /* EOF(=^Z或F6),NULL */
#include <stdlib.h>  /* atoi() */
#include <string.h>
/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define INFEASIBLE -1
// 顺序表
#define MAXNUM 100    /* 表示线性表可能达到的最大长度 */
typedef int DataType; /* 数据元素类型定义 */
typedef struct {
    DataType data[MAXNUM]; /* 存放线性表的数据元素 */
    int last;              /* 用来存放线性表最后一个数据元素在数组中的下标 */
    int length;
} SeqList;
// 1.顺序表定位
int SeqLLocate(SeqList l, DataType x) {
    int i;
    for (i = 0; i < l.length; i++) {
        if (l.data[i] == x)
            return (i + 1);
        return 0;
    }
}
// 2.顺序表插入
int SeqLInsert(SeqList l, int i, DataType x) {
    int j;
    if (l.length == MAXNUM - 1) {
        printf("溢出");
        return 0;
    }
    if (i < 1 || i > l.length) {
        printf("位置不正确");
        return 0;
    }
    for (j = l.length - 1; j >= i - 1; j--)
        l.data[j + 1] = l.data[j];
    l.data[i - 1] = x;
    l.length++;
}
// 3.顺序表删除
int SeqLDelete(SeqList l, int i) {
    int j;
    if (i < 1 || i > l.length) {
        printf("位置不正确");
        return 0;
    }
    for (j = i; j < l.length - 1; j++)
        l.data[j - 1] = l.data[j];
    return 1;
}
// 建立顺序表
void SeqLCreate(SeqList l) {
    int i, n;
    printf("\t请输入表的长度:");
    scanf("%d", &n);
    l.length = n;
    printf("\t依次输入表中的数据元素（整数）:\n");
    for (i = 0; i < n; i++) {
        printf("\t第%d个元素是:", i + 1);
        scanf("%d", &l.data[i]);
    }
}

// 链表
typedef struct node /* 结点类型定义 */
{
    DataType data;
    struct node *next;
} LinkedList;
// 5.求单链表长度
int GetLListLength(LinkedList *l) {
    LinkedList *p;
    int j = 0;
    p = l->next;
    while (p != NULL) {
        p = p->next;
        j++;
    }
    return j;
}
// 6.单链表取节点
LinkedList *GetLListElem(LinkedList *L, int i) {
    int j = 0;
    LinkedList *p;
    p = L;
    while ((p->next != NULL) && (j < 1)) {
        p = p->next;
        j++;
    }
    if (i == j)
        return p;
    else
        return NULL;
}
// 7.单链表定位
LinkedList *LocateLListElem(
    LinkedList *L,
    DataType key) /*在带头结点的单链表L中查找其结点值等于key的结点，若找到则返回该结点的位置p，否则返回NULL*/
{
    LinkedList *p;
    p = L->next; /* 从表中第一个结点开始 */
    while (p != NULL) {
        if (p->data != key)
            p = p->next;
        else
            break; /* 找到结点值=key时退出循环 */
    }
    return p;
}
// 8.单链表插入
int InsertLList(LinkedList *L, int i, DataType x) { /*在带头结点的单链表L中第i个位置插入值为e的新结点s*/
    LinkedList *pre, *s;
    int k;
    pre = L;
    k = 0;                           /* 从"头"开始，查找第i-1个结点 */
    while (pre != NULL && k < i - 1) /* 表未查完且未查到第i-1个时重复，找到pre指向第i-1个 */
    {
        pre = pre->next;
        k = k + 1;
    } /* 查找第i-1结点 */
    if (!pre) /* 如当前位置pre为空表，说明插入位置不合理 */
    {
        printf("插入位置不合理!");
        return 0;
    }
    s = (LinkedList *)malloc(sizeof(LinkedList)); /* 申请一个新的结点s */
    s->data = x;                                  /* 值x置入s的数据域 */
    s->next = pre->next;                          /* 修改指针，完成插入操作 */
    pre->next = s;
    return 1;
}
// 9.单链表删除
int DeleteLList(LinkedList *L, int i,
                DataType *e) { /*在带头结点的单链表L中删除第i个元素，并将删除的元素保存到变量*e中*/
    LinkedList *pre, *r;
    int k;
    pre = L;
    k = 0;
    while (pre->next != NULL && k < i - 1) /* 寻找被删除结点i的前驱结点i-1使p指向它 */
    {
        pre = pre->next;
        k = k + 1;
    } /* 查找第i-1个结点 */
    if (!(pre->next)) /* 即while循环是因为p->next=NULL或i<1而跳出的,*/
    {                 /*而是因为没有找到合法的前驱位置，说明删除位置i不合法。*/
        printf("删除结点的位置i不合理!");
        return 0;
    }
    r = pre->next;
    pre->next = pre->next->next; /* 修改指针，删除结点r */
    *e = r->data;
    free(r); /* 释放被删除的结点所占的内存空间 */
    printf("成功删除结点!");
    return 1;
}
// 10.头插法建表
LinkedList *CreateLList() {
    char ch;
    LinkedList *head, *s;
    head = NULL;
    ch = getchar();
    while (ch != '$') /* 循环输入表中元素值，将建立的新结点s插入表头，输入'$'结束 */
    {
        s = (LinkedList *)malloc(sizeof(LinkedList));
        s->data = ch;
        s->next = head;
        head = s;
        ch = getchar();
    }
    return head;
}
// 11.尾插法建表
LinkedList *CreateLListR() {
    char ch;
    LinkedList *head, *s, *r;
    head = (LinkedList *)malloc(sizeof(LinkedList));
    r = head;
    ch = getchar();
    while (ch != '$') /* 循环输入表中元素值，将建立的新结点s插入表尾，输入'$'结束 */
    {
        s = (LinkedList *)malloc(sizeof(LinkedList));
        s->data = ch;
        r->next = s;
        r = s;
        ch = getchar();
    }
    r->next = NULL; /* 将最后一个结点的next链域置为空，表示链表的结束 */
    return head;
}
/////////////////////////////////////////////
/////////////////////////////////////////////
// 顺序栈
typedef struct /*顺序栈定义*/
{
    DataType data[MAXNUM]; /*  存放栈的数据元素  */
    int top;               /*  栈顶指针，用来存放栈顶元素在数组中的下标  */
} SeqStack;
// 入栈
int SStackPush(SeqStack *s, DataType x) {
    if (s->top == MAXNUM) {
        printf("栈上溢出!\n");
        return 0;
    } else {
        s->top++;
        s->data[s->top] = x;
        return 1;
    }
}
// 出栈
int SStackPop(SeqStack *s, DataType *x) {
    if (s->top == -1) {
        printf("栈下溢出!\n");
        return 0;
    } else {
        *x = s->data[s->top];
        s->top--;
        return 1;
    }
}
/////////////////////////////////////////
/////////////////////////////////////////
// 链栈
typedef struct node {
    DataType data;     /*数据域*/
    struct node *next; /*指针域*/
} LinkStack;           /*链栈结点类型*/
// 14.初始化链栈
LinkStack *LStackInit() {
    LinkStack *h = (LinkStack *)malloc(sizeof(LinkStack));
    h->data = 1;
    h->next = NULL;
    return h;
}
// 15.入链栈
LinkStack *LStackPush(LinkStack *ls, DataType x) /*入栈*/
{
    LinkStack *p;
    p = (LinkStack *)malloc(sizeof(LinkStack)); /*分配空间*/
    p->data = x;                                /*设置新结点的值*/
    p->next = ls;                               /*将新元素插入栈中*/
    ls = p;                                     /*将新元素设为栈顶*/
    return ls;
}
// 16.出链栈
LinkStack *LStackPop(LinkStack *ls, DataType *e) /*出栈*/
{
    LinkStack *p;
    if (!ls) /*判断是否为空栈*/
    {
        printf("\n链栈是空的!");
        return NULL;
    }
    p = ls;        /*指向被删除的栈顶*/
    *e = p->data;  /*返回栈顶元素*/
    ls = ls->next; /*修改栈顶指针*/
    free(p);
    return ls;
}
/////////////////////////////////////////////
////////////////////////////////////////////
// 顺序队列
typedef struct /*顺序队列类型定义*/
{
    int front, rear;
    DataType data[MAXNUM];
} SeqQueue;
// 17.创建空队列
SeqQueue *SQueueCreate() /*创建一个空队列*/
{
    SeqQueue *sq = (SeqQueue *)malloc(sizeof(SeqQueue));
    if (sq == NULL)
        printf("溢出!! \n");
    else
        sq->front = sq->rear = 0;
    return sq;
}
// 18.入队
void SQueueEnQueue(SeqQueue *sq, DataType x) /* 循环队列的进队操作，x进队 */
{
    if ((sq->rear + 1) % MAXNUM == sq->front) /*  修改队尾指针  */
        printf("队列满!\n");
    else {
        sq->data[sq->rear] = x;
        sq->rear = (sq->rear + 1) % MAXNUM;
    }
}
// 19.出队
int SQueueDeQueue(SeqQueue *sq, DataType *e)
/* 循环队列的出队操作，出队元素存入e中 */
{
    if (sq->front == sq->rear) {
        printf("队空!\n");
        return 0;
    } else {
        *e = sq->data[sq->front];
        sq->front = (sq->front + 1) % MAXNUM; /*  修改队头指针  */
        return 1;
    }
}

// 链队列
typedef struct LQNode /* 链队结点结构 */
{
    DataType info;
    struct LQNode *next;
} LQNode;
typedef struct /* 链接队列类型定义 */
{
    struct LQNode *front; /* 头指针 */
    struct LQNode *rear;  /* 尾指针 */
} LinkQueue;
// 20.创建空链队
LinkQueue *LQueueCreateEmpty() /*创建空链队,返回头指针*/
{
    LinkQueue *plq = (LinkQueue *)malloc(sizeof(LinkQueue));
    if (plq != NULL)
        plq->front = plq->rear = NULL;
    else {
        printf("内存不足!! \n");
        return NULL;
    }
    return plq;
}
// 21.入链队
void LQueueEnQueue(LinkQueue *plq, DataType x) /*入链队*/
{
    LQNode *p = (LQNode *)malloc(sizeof(LQNode));
    if (p = NULL)
        printf("内存分配失败");
    else {
        p->info = x;
        p->next = NULL;
        if (plq->front == NULL)
            plq->front = p;
        else
            plq->rear->next = p;
        plq->rear = p;
    }
}
// 22.出链队
int LQueueDeQueue(LinkQueue *plq, DataType *x) /*出链队*/
{
    LQNode *p;
    if (plq->front == NULL) {
        printf("队列空!!\n ");
        return ERROR;
    } else {
        p = plq->front;
        *x = p->info;
        plq->front = plq->front->next;
        free(p);
        return 1;
    }
}
// 串
#define MAXSTRLEN 255                         // 用户可在255以内定义最大串长
typedef unsigned char SString[MAXSTRLEN + 1]; // 0号单元存放串的长
// 23.串匹配
int Index(SString S, SString T, int pos) {
    // 返回子串T在主串S第pos个字符之后的位置。若不存在，则函数值为0。其中，T非空，1≤pos≤StrLength(S)。
    int i = pos;
    int j = 1;
    while (i <= S[0] && j <= T[0]) {
        if (S[i] == T[j]) {
            ++i;
            ++j;
        } // 继续比较后继字符
        else {
            i = i - j + 2;
            j = 1;
        } // 指针后退重新开始匹配
    }
    if (j > T[0])
        return i - T[0];
    else
        return 0;
}
