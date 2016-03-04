//
//  main.c
//  call－book
//
//  Created by 何灏 on 16/3/4.
//  Copyright © 2016年 UESTCOpenSource. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct { //通讯录结点类型
    char num[5];   //编号
    char name[9]; //姓名
    char sex[3];    //性别
    char phone[13]; //电话
    char addr[31]; //地址
} DataType;
typedef struct node {   //结点类型定义
    DataType data;    //结点数据域
    struct node *next; //结点指针域
} ListNode;
typedef ListNode *LinkList;
LinkList head;
ListNode *p;
//函数说明
int menu_select();
LinkList CreateList(void);
void InsertNode(LinkList head,ListNode *p);
ListNode *ListFind(LinkList head);
void DelNode(LinkList head);
void printList(LinkList head);
//主函数
int main()
{
    for( ; ; ){
        switch(menu_select( ) )
        {
            case 1:
                printf("**********************************\n");
                printf("*    通 讯 录 链 表 的 建 立     *\n");
                printf("**********************************\n");
                head=CreateList( );
                break;
            case 2:
                printf("**********************************\n");
                printf("*    通 讯 者 信 息 的 添 加     *\n");
                printf("**********************************\n");
                printf("编号(4) 姓名(8) 性别(3) 电话(11) 地址(31)\n");
                printf("************************************* \n");
                p=(ListNode *)malloc(sizeof(ListNode)); //申请新结点
                scanf("%s%s%s%s%s",p->data.num,p->data.name,p->data.sex,
                      p->data.phone,p->data.addr);
                InsertNode(head,p);
                break;
            case 3:
                printf("***********************************\n");
                printf("*     通 讯 录 信 息 的 查 询     *\n");
                printf("***********************************\n");
                p=ListFind(head);
                if (p!=NULL) {
                    printf("编号 姓 名 性别 联系电话 地址 \n");
                    printf("--------------------------------------------------\n");
                    printf("%s,%s,%s,%s,%s\n",p->data.num,p->data.name,
                           p->data.sex,p->data.phone,p->data.addr);
                    printf("---------------------------------------------------\n");
                }
                else
                    printf("没有查到要查询的通讯者！\n");
                break;
            case 4:
                printf("***********************************\n");
                printf("*    通 讯 录 信 息 的 删 除      *\n");
                printf("***********************************\n");
                DelNode(head); //删除结点
                break;
            case 5:
                printf("************************************\n");
                printf("*     通 讯 录 链 表 的 输 出      *\n");
                printf("************************************\n");
                printList(head);
                break;
            case 0:
                printf("\t 再 见！ \n");
                return 0;
        }
    }
}
/*******************/
/* 菜单选择函数程序        */
/***************************/
int menu_select( )
{
    int sn;
    printf("     通讯录管理系统 \n");
    printf("===================\n");
    printf("    1.通讯链表的建立\n");
    printf("    2.通讯者结点的插入\n");
    printf("    3.通讯者结点的查询\n");
    printf("    4.通讯者结点的删除\n");
    printf("    5.通讯录链表的输出\n");
    printf("    0.退出管理系统\n");
    printf("==========================\n");
    printf("    请 选 择 0-5： ");
    for( ; ; )
    {
        scanf("%d",&sn);
        if (sn<0||sn>5)
            printf("\n\t输入错误，重选0-5:");
        else
            break;
    }
    return sn;
}
/**************************/
/*用尾插法建立通讯录链表函数       */
/**************************/
LinkList CreateList(void)
{//尾插法建立带头结点的通讯录链表算法
    LinkList head=(ListNode *)malloc(sizeof(ListNode)); //申请头结点
    ListNode *p,*rear;
    int flag=0;   //结束标志置0
    rear=head; //尾指针初始指向头结点
    while (flag==0)
    { p=(ListNode *)malloc(sizeof(ListNode));    //申新结点
        printf("编号(4) 姓名(8) 性别 电话(11)   地址(31)\n");
        printf("--------------------------------------------------------------------------------------\n");
        scanf("%s%s%s%s%s",p->data.num,p->data.name,p->data.sex,p->data.phone,
              p->data.addr);
        rear->next=p;        //新结点连接到尾结点之后
        rear=p;             //尾指针指向新结点
        printf("结束建表吗?(1/0):");
        scanf("%d",&flag);
    }
    rear->next=NULL;       //终端结点指针置空
    return head;            //返回链表头指针
}
/******************************/
/*在通讯录链表head中插入结点 */
/******************************/
void InsertNode(LinkList head,ListNode *p)
{
    ListNode *p1,*p2;
    p1=head;
    p2=p1->next;
    while(p2!=NULL && strcmp(p2->data.num,p->data.num)<0)
    {
        p1=p2;     //p1指向刚访问过的结点
        p2=p2->next;   //p2指向表的下一个结点
    }
    p1->next=p;    //插入p所指向的结点
    p->next=p2;    //连接表中剩余的结点
}
/******************************************/
/*   有序通讯录链表的查找          */
/******************************************/
ListNode *ListFind(LinkList head)
{// 有序通讯录链表上的查找
    ListNode *p;
    char num[5];
    char name[9];
    int xz;
    printf("==================\n");
    printf(" 1. 按编号查询     \n");
    printf(" 2. 按姓名查询     \n");
    printf("==================\n");
    printf("     请 选 择：     ");
    p=head->next;   //假定通讯 录表带头结点
    scanf("%d",&xz);
    if (xz==1) {
        printf("请输入要查找者的编号：");
        scanf("%s",num);
        while (p&&strcmp(p->data.num,num)<0)
            p=p->next;
        if ((p==NULL)||strcmp(p->data.num,num)<0)
        p=NULL;     //没有查到要查找的通讯者
    }
    else
        if (xz==2) {
            printf(" 请输入要查找者的姓名：");
            scanf("%s",name);
            while(p&&strcmp(p->data.name,name)!=0)
                p=p->next;
        }
    return p;
}
/*******************************/
/*     通讯录链表上的结点删除    */
/*********************************/
void DelNode(LinkList head)
{
    char jx;
    ListNode *p,*q;
    p=ListFind(head);   //调用查找函数
    if (p==NULL) {
        printf("没有查到要删除的通讯者!\n");
        return;
    }
    printf("真的要删除该结点吗？（y/n）:");
    scanf("%c",&jx);
    if (jx=='y'||jx=='Y') {
        q=head;
        while ((q!=NULL) &&(q->next!=p))
            q=q->next;
        q->next=p->next;    //删除结点
        free(p);            //释放被删结点空间
        printf("通讯者已被删除！\n");
    }
}
/**********************************/
/*   通讯录链表的输出函数         */
/**********************************/
void printList(LinkList head)
{
    ListNode *p;
    p=head->next;
    printf("编号 姓 名    性别    联系电话    地址      \n");
    printf("--------------------------------------------------------------------------------\n");
    while (p!=NULL)
    { printf("%s,%s,%s,%s,%s\n",p->data.num,p->data.name,p->data.sex,
             p->data.phone,p->data.addr);
        printf("---------------------------------------------------------------------------------\n");
        p=p->next;          //后移一个结点
    }
}