#include <iostream>
using namespace std;
#define SIS 100
#define STAKE 10
	struct Stack
	{
		char*base;
		char*top;
		int stacksize;
	};
	struct DStack
	{
		double*base;
		double*top;
		int stacksize;
	};
	double Evar(char m[]);
	int Stack_Init(Stack&S);
	int Init_DStackk(DStack&S);
	int Push(Stack &S,char e);
	int DPush(DStack &S,double e);
	int Pop(Stack &S,char &e);
	int DPop(DStack &S,double &e);
	char GetTop(Stack &S);
	double DGetTop(DStack &S);
	double Operate(double a, char theta, double b);
	int In(char c);
	char Precd(char c1,char c2);//函数声明

	int main()
	{
		while(1)
		{
			cout<<"输入表达式，表达式以=结束"<<endl;
			char m[50];
			cin>>m;
			double c;
			c=Evar(m);
			cout<<"此算术表达式的结果为"<<c<<endl;
		}
			return 0;	
	}

	double Evar(char m[]) 
	{ //算术表达式求值，OPTR和OPDN分别为运算符栈和操作数栈
	   Stack OPTR;   
	   DStack OPND;
	   Stack_Init (OPTR);
	   Push (OPTR, '=');
	   Init_DStackk (OPND);
	   double a , b;
	   int i=0;
	   char c,theta;
		while( m[i]!='=' || GetTop(OPTR) !='=' )
		{
		   if( !In(m[i]) )      // 操作数
		   {
			   char *p;
			   p=&m[i];
			   while(!In(m[i])||m[i]=='.'){i++;}
			   DPush(OPND,atof(p));
		   }
		   else//运算符
		   switch( Precd(GetTop(OPTR) , m[i] ) )
			{
				case '<'://当前运算符等级高
				Push(OPTR,m[i]);
				i++;
				break;

				case '=':
				Pop(OPTR,c);
				i++;
				break;
				case '>':
				Pop(OPTR,theta);
				DPop(OPND,b);//弹出两个数
				DPop(OPND,a);
				DPush(OPND,Operate(a , theta , b));
				break;
			}
		 }
		return DGetTop(OPND) ;
	}
	int Stack_Init(Stack&S) //构造运算符栈
	{
		S.base = new char[SIS] ;
		if(!S.base) cout<<"分配失败"<<endl;
		S.top = S.base;
		S.stacksize = SIS;
		return 1;
	}
	int Init_DStackk(DStack&S) //构造操作数栈
	{
		S.base = new double[SIS];
		if(!S.base) cout<<"分配失败"<<endl;
		S.top = S.base;
		S.stacksize = SIS;
		return 1;
	}

	int Push(Stack &S,char e)//运算符进栈
	{
		if(S.top-S.base>=S.stacksize){
		S.base=new char[S.stacksize+STAKE];
			if(!S.base) cout<<"分配失败"<<endl;
		S.top=S.base+S.stacksize;
		S.stacksize+=STAKE;
		}
			*S.top++ = e;
			return 1;
	}

	int DPush(DStack &S,double e)//操作数进栈
	{
		if(S.top-S.base>=S.stacksize)
		{
			S.base=new double[S.stacksize+STAKE];
				if(!S.base) cout<<"分配失败"<<endl;
			S.top=S.base+S.stacksize;
			S.stacksize+=STAKE;
		}
		*S.top++ = e;
		return 1;
	}
	int Pop(Stack &S,char &e)//运算符出栈
	{
		if (S.top==S.base) return 0;
		e=*--S.top;
		return 1;
	}
	int DPop(DStack &S,double &e)//操作数出栈
	{
		if (S.top==S.base) return 0;
		e=*--S.top;
		return 1;
	}
	char GetTop(Stack &S)//返回运算符的栈顶元素
	{
		char e;
		if(S.top==S.base) return 0;
		e=*(S.top-1);
		return e;
	}
	double DGetTop(DStack &S)//返回操作数的栈顶元素
	{
		double e;
		if(S.top==S.base) return 0;
		e=*(S.top-1);
		return e;
	}
	double Operate(double a,char theta, double b) 
	{//计算
	   switch(theta) 
	   {
		 case '+': return a+b;break;
		 case '-': return a-b;break;
		 case '*': return a*b;break;
		 case '/': if(b!=0) {return a/b;break;}
			 else cout<<"分母不能为零！,输入错误"<<endl;
	   default: return 0;
		}
	}

	int In(char c)
	{//判断是否为操作数
		if(c!='+'&&c!='-'&&c!='*'&&c!='/'&&c!='('&&c!=')'&&c!='=') return 0;
		else return 1;
	}

	char Precd(char c1,char c2)
	{//比较运算符之间的优先级
		switch(c1)
		{
			case '+':if(c2=='+'||c2=='-'||c2==')'||c2=='=') return '>';
				else return '<';break;
			case '-':if(c2=='+'||c2=='-'||c2==')'||c2=='=') return '>';
				else return '<';break;
			case '*':if(c2=='(') return '<';
				else return '>';break;
			case '/':if(c2=='(') return '<';
				else return '>';break;
			case '(':if(c2==')') return '=';
					  else return '<';break;
			case ')': return '>';break;
			case '=':if(c2=='=') return '=';
					  else return '<';break;
			default:return 0;
		}
	}


/*			6x(5+(2+3)x8+3)=

  OPTR   OPDN			OPTR   OPDN			OPTR   OPDN			OPTR   OPDN			OPTR   OPDN			OPTR   OPDN
		  )				 5		+			 8       *			 40		+				     )			 48		
		  +				 5		(			 5		 +			  5		(			  3		 +		      6	     *
	3	  (		==》	 6		*     ==》   5		 (	  ==》	  6		*	  ==》	 45		 (	   ==》
	2	  +									 6		 *								  6		 *
	5     (
	6     *
*/