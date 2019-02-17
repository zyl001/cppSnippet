#include <iostream>
#include <algorithm>
#include <vector>

//true std::sort操作的容器中，则i在j的前面
bool cmp(int i, int j)
{
	if (i<j)
	{
		return false;
	}
	else
	{
		return true;
	}
}
int main(void) {


	int a[] = { 1,2,3,4,5,6,6,6,7,8,9,12,17};
	int len = (sizeof a) / sizeof a[0];
	int pos = std::lower_bound(a, a + len, 6) - a;//升序时第一个大于等于val的值
	pos = std::upper_bound(a, a + len, 9) - a;//升序时第一个大于val的值

	int a1[] = { 2,7,5.4,3,1,9 };
	std::sort(a1, a1 + (sizeof a1) / sizeof a1[0]);//sort默认升序排序
	int a2[] = { 2,7,5.4,3,1,9 };
	std::sort(a2, a2 + (sizeof a2) / sizeof a2[0],cmp);
	std::vector<int> v(a2, a2 + (sizeof a2) / sizeof a2[0]);
	pos = std::lower_bound(v.begin(), v.end(), 3, cmp) -v.begin();//TODO还没通俗理解
	pos = std::upper_bound(v.begin(), v.end(), 3, cmp) - v.begin();

	pos = std::lower_bound(v.begin(), v.end(), 3) - v.begin();
	pos = std::upper_bound(v.begin(), v.end(), 3) - v.begin();


	return 0;

}