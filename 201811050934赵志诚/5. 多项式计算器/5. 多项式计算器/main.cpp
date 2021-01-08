//
//  main.cpp
//  5. 多项式计算器
//
//  Created by 赵志诚 on 2021/1/5.
//  Copyright © 2021年 赵志诚. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

#define OK 10000
#define ERROR 10001

struct node
{
    int data;
    struct node *next;
};
typedef struct node Node;

struct stack
{
    Node *top;
    int count;
};
typedef struct stack Stack;

int InitStack(Stack *S) //初始化
{
    S->top = NULL;
    S->count = 0;
    
    return OK;
}

int EmptyStack(Stack *S)  //判断是否为空
{
    return (S->count == 0) ? OK : ERROR;
}

int Push(Stack *S,int e) //头插法
{
    Node *p = (Node *)malloc(sizeof(Node));//p为新栈顶    申请空间
    if(NULL == p)
    {
        return ERROR;
    }
    p->data = e;
    p->next = S->top;//s->top为原栈顶
    S->top = p;
    S->count++;
    
    return OK;
}

int GetTop(Stack *S)
{
    if(NULL == S->top)
    {
        return ERROR;
    }
    
    return (S->top->data);
}

int Priority(char s)
{
    switch(s)
    {
        case'(':
            return 3;
        case'*':
        case'/':
            return 2;
        case'+':
        case'-':
            return 1;
        default:
            return 0;
    }
}
int Pop(Stack *S)
{
    int e;
    
    if(NULL == S->top)
    {
        return ERROR;
    }
    Node *p = S->top;
    e = p->data;
    S->top = p->next;
    free(p);
    S->count--;
    return e;
}
int main()
{
    Stack num, opt;//两个栈一个储存数字一个储存运算符
    char str[100] ={0};
    int i = 0,tmp = 0,j;
    if (InitStack(&num) !=OK || InitStack(&opt) !=OK)
    {
        printf("初始化失败\n");
        exit(1);  //表示退出异常
    }
    printf("请输入算式:\n");
    scanf("%s",str);
    while(str[i] !='\0' || EmptyStack(&opt) !=OK)//不为空
    {
        if (str[i] >= '0' && str[i] <='9')   //如果是数字
        {
            tmp = tmp * 10 + str[i] - '0';  //将个位转为十位  百位
            i++;
            if (str[i] < '0' || str[i] >'9') //i++后如果不是数字 入栈后清零tmp
            {
                Push(&num,tmp);
                tmp = 0;
            }
        }
        else
        {
            if ((EmptyStack(&opt) ==OK) || (GetTop(&opt)=='(' && str[i] !=')')|| //进栈不运算
                (Priority(str[i])>Priority(GetTop(&opt))))//运算等级大于栈顶运算等级
            {
                Push(&opt,str[i]);//入栈
                i++;
                continue;
            }
            
            if (GetTop(&opt)=='(' && str[i] ==')')  //出栈不运算   两个括号
            {
                Pop(&opt); //出栈
                i++;
                continue;// 结束当前循环
            }
            
            if ((str[i]=='\0' && EmptyStack(&opt) !=OK) || (str[i]==')' && GetTop(&opt) !='(')||  //出栈运算
                (Priority(str[i])<=Priority(GetTop(&opt))))  //注意没有i++;
            {
                switch(Pop(&opt))
                {
                    case '+':
                        Push(&num,Pop(&num)+Pop(&num));
                        break;
                    case '-':
                        j = Pop(&num);
                        Push(&num,Pop(&num)-j);
                        break;
                    case '*':
                        Push(&num,Pop(&num)*Pop(&num));
                        break;
                    case '/':
                        j = Pop(&num);
                        Push(&num,Pop(&num)/j);
                        break;
                }
                continue;
                
            }
        }
    }
    
    printf("结果为 :%d\n",Pop(&num));
    return 0;
}
