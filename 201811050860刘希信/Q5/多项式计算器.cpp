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
 
int InitStack(Stack *S) //��ʼ��
{
	S->top = NULL;
	S->count = 0;
 
    return OK;
}
 
int EmptyStack(Stack *S)  //�ж��Ƿ�Ϊ��
{
	return (S->count == 0) ? OK : ERROR;
}
 
int Push(Stack *S,int e) //ͷ�巨
{
    Node *p = (Node *)malloc(sizeof(Node));//pΪ��ջ��    ����ռ�
    if(NULL == p)
    {
        return ERROR;
    }
    p->data = e;
    p->next = S->top;//s->topΪԭջ�� 
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
	Stack num, opt;//����ջһ����������һ�����������
	char str[100] ={0};
	int i = 0,tmp = 0,j;
	if (InitStack(&num) !=OK || InitStack(&opt) !=OK)
	{
		printf("��ʼ��ʧ��\n");
		exit(1);  //��ʾ�˳��쳣
	}
	printf("��������ʽ:\n");
	scanf("%s",str);
	while(str[i] !='\0' || EmptyStack(&opt) !=OK)//��Ϊ��
	{
		if (str[i] >= '0' && str[i] <='9')   //��������� 
		{
			tmp = tmp * 10 + str[i] - '0';  //����λתΪʮλ  ��λ
			i++;
			if (str[i] < '0' || str[i] >'9') //i++������������� ��ջ������tmp
			{
				Push(&num,tmp);
				tmp = 0;
			}
		}
		else
		{
			if ((EmptyStack(&opt) ==OK) || (GetTop(&opt)=='(' && str[i] !=')')|| //��ջ������
					(Priority(str[i])>Priority(GetTop(&opt))))//����ȼ�����ջ������ȼ�
			{
				Push(&opt,str[i]);//��ջ
				i++;
				continue;
			}
 
			if (GetTop(&opt)=='(' && str[i] ==')')  //��ջ������   ��������
			{
				Pop(&opt); //��ջ
				i++;
				continue;// ������ǰѭ��
			}
 
			if ((str[i]=='\0' && EmptyStack(&opt) !=OK) || (str[i]==')' && GetTop(&opt) !='(')||  //��ջ����
					(Priority(str[i])<=Priority(GetTop(&opt))))  //ע��û��i++;
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
				continue;			}
		}
	}
 
	printf("���Ϊ :%d\n",Pop(&num));
	return 0;
}


//   ((1+2)*3+4)+5+6*7
//    opt           num             opt      num             opt       num           opt        num        opt     num        
//
//
//    ��+                   ��                      ��                         ��                     ��                    
//    ��(          ��2             ��(                      ��*         ��3         ��+         ��4         
//    ��(          ��1             ��(      ��3             ��(         ��3         ��(         ��9        ��(     ��13       
//
//    opt           num             opt      num             opt       num           opt        num        opt     num
//  
//                                
//    ��*          ��7      ��                      ��                         ��                     ��
//    ��+          ��6               +        42                 
//    ��+          ��5               +        5               +         47                    
//                  13                        13                        13                       60                 60