#include <stdio.h>
#include <math.h>
#include <utility>
#include <map>
#include <string.h>

int main() {
	int testCase;
	int limitTime, countOfMem; // 제한 시간, 사람의 개수
	int max = 0; // 최대값
	int begin = 0, finish = 0; // 시작점, 끝점을 입력받고 이를 Data로 넣는다.
	int start = 0, end = 0;
	std::multimap<int,int> dataMap; // key, value 데이터를 가진 dataMap (중복을 허용한다)
	std::multimap<int, int>::iterator it; // iterator
	std::multimap<int, int>::iterator selectedIt; //선택된 iterator

	scanf("%d", &testCase);
	for (testCase; testCase > 0; testCase--) {
		max = 0; // 최대 count
		scanf("%d %d", &limitTime, &countOfMem); // 제한 시간, 멤버수
		for (i = 0; i < countOfMem; i++) {
			scanf("%d %d", &start, &end);
			dataMap.insert(std::pair<int,int>(start,end)); // 시작과 끝을 MultiMap으로 관리한다.
		}
		
		it = dataMap.begin(); // 시작
		while (it != dataMap.end()) {
			if (it == dataMap.begin()) {
				selectedIt = it; // 시작부분엔 기준 iterator를 it으로 초기화
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
			max++;  // 루프를 빠져나오면서, 선택된 iterator는 계산이 되지 않았기 때문에, 1 증가시킨다.
		}
		printf("%d\n", max);
		dataMap.clear();
	}
	return 0;
}