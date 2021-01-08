#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
struct Stu {
	int id;
	int yuwen;
	int shuxue;
	int yingyu;
	int zongfeng;
}stu[305];
bool cmp(struct Stu a, struct Stu b) {
	if (a.zongfeng != b.zongfeng) {
		return a.zongfeng > b.zongfeng;
	}
	else {
		if (a.yuwen != b.yuwen) {
			return a.yuwen > b.yuwen;
		}
		else {
			return a.id < b.id;
		}
	}
}
int main() {
	int n, i;
	scanf_s("%d", &n);
	for (i = 0; i < n; ++i) {
		stu[i].id = i + 1;
		scanf_s("%d %d %d", &stu[i].yuwen, &stu[i].shuxue, &stu[i].yingyu);
		stu[i].zongfeng = stu[i].yuwen + stu[i].shuxue + stu[i].yingyu;
	}
	sort(stu, stu + n, cmp);
	for (i = 0; i < 5; ++i) {
		printf("%d %d\n", stu[i].id, stu[i].zongfeng);
	}
	return 0;
}