#include<stdio.h>

void reverse_seq(int a[]){
    int tmp=0;
    for (int i = 0, j = len(a)-1; i < j;i++,j--) {
        tmp = a[j];
        a[j] = a[i];
        a[i] = tmp;
    }
}

void reverse_linklist(ListNode head){
    LNode cur, pre = head, None;
    while(cur){
        LNode tmp = cur.next;
        cur.next=pre;
        pre = cur;
        cur = tmp;
    }
}

LNode merge(LinkList A, LinkList B) {
    LNode dum = cur = None;
    while(A&&B){
        cur.next = A;
        cur = cur.next;
        cur.next = B;
        cur = cur.next;
        A = A.next;
        B = B.next;
    }
    if A
        cur.next = A;
    else
        cur.next = B;
    return dum.next
}