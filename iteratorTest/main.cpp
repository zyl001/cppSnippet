#include <iostream>
#include <algorithm>
#include <vector>

//true std::sort�����������У���i��j��ǰ��
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
	int pos = std::lower_bound(a, a + len, 6) - a;//����ʱ��һ�����ڵ���val��ֵ
	pos = std::upper_bound(a, a + len, 9) - a;//����ʱ��һ������val��ֵ

	int a1[] = { 2,7,5.4,3,1,9 };
	std::sort(a1, a1 + (sizeof a1) / sizeof a1[0]);//sortĬ����������
	int a2[] = { 2,7,5.4,3,1,9 };
	std::sort(a2, a2 + (sizeof a2) / sizeof a2[0],cmp);
	std::vector<int> v(a2, a2 + (sizeof a2) / sizeof a2[0]);
	pos = std::lower_bound(v.begin(), v.end(), 3, cmp) -v.begin();//TODO��ûͨ�����
	pos = std::upper_bound(v.begin(), v.end(), 3, cmp) - v.begin();

	pos = std::lower_bound(v.begin(), v.end(), 3) - v.begin();
	pos = std::upper_bound(v.begin(), v.end(), 3) - v.begin();


	return 0;

}