#include <iostream>

int fun_return(int a,int b){
	int c=10*(b%10)+100*(a/10)+1000*(b/10)+(a%10);
	return c;
}
void fun_refer(int a,int b,int &c){
	c=10*(b%10)+100*(a/10)+1000*(b/10)+(a%10);
}
void fun_pointer(int a,int b,int *c){
	*c=10*(b%10)+100*(a/10)+1000*(b/10)+(a%10);
}
/*
int main() {
	int a;
	int b;
	int c;
	printf("请输入第一个两位数a:");
	scanf("%d",&a);
	printf("请输入第二个两位数b:");
	scanf("%d",&b);
	c=fun_return(a,b);
	printf("结果为:%d",c);
	return 0;
}

int main() {
	int a;
	int b;
	int c;
	printf("请输入第一个两位数a:");
	scanf("%d",&a);
	printf("请输入第二个两位数b:");
	scanf("%d",&b);
	fun_refer(a,b,c);
	printf("结果为:%d",c);
	return 0;
}
*/
int main() {
	int a;
	int b;
	int c;
	printf("请输入第一个两位数a:");
	scanf("%d",&a);
	printf("请输入第二个两位数b:");
	scanf("%d",&b);
	fun_pointer(a,b,&c);
	printf("结果为:%d",c);
	return 0;
}
