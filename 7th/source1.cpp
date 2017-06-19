#include <stdio.h>
#include <math.h>
#include <utility>
#include <map>
#include <string.h>

int main() {
	int testCase;
	int limitTime, countOfMem; // ���� �ð�, ����� ����
	int max = 0; // �ִ밪
	int begin = 0, finish = 0; // ������, ������ �Է¹ް� �̸� Data�� �ִ´�.
	int start = 0, end = 0;
	std::multimap<int,int> dataMap; // key, value �����͸� ���� dataMap (�ߺ��� ����Ѵ�)
	std::multimap<int, int>::iterator it; // iterator
	std::multimap<int, int>::iterator selectedIt; //���õ� iterator

	scanf("%d", &testCase);
	for (testCase; testCase > 0; testCase--) {
		max = 0; // �ִ� count
		scanf("%d %d", &limitTime, &countOfMem); // ���� �ð�, �����
		for (i = 0; i < countOfMem; i++) {
			scanf("%d %d", &start, &end);
			dataMap.insert(std::pair<int,int>(start,end)); // ���۰� ���� MultiMap���� �����Ѵ�.
		}
		
		it = dataMap.begin(); // ����
		while (it != dataMap.end()) {
			if (it == dataMap.begin()) {
				selectedIt = it; // ���ۺκп� ���� iterator�� it���� �ʱ�ȭ
				it++;
				continue;
			}
			if (selectedIt->second <= it->first) {
				max++;
				selectedIt = it;
			}
			if (selectedIt->first <= it->first && it->second < selectedIt->second) {
				selectedIt = it;
			}
			it++;
		}
		if (selectedIt != dataMap.end()) {
			max++;  // ������ ���������鼭, ���õ� iterator�� ����� ���� �ʾұ� ������, 1 ������Ų��.
		}
		printf("%d\n", max);
		dataMap.clear();
	}
	return 0;
}