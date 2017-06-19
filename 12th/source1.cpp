#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>

#define MAX_COUNT 2501
int arr[MAX_COUNT];

int main() {
	int tc, i, j, k; // loop iterator
	int v_count, l_count; // 기둥 개수, 레벨 개수
	int data, temp, index; // 자료구조로 부터 빼낼 데이터, 임시값, 위치
	int start, target; //시작 지점, 목표지점	
	bool bFind = false;

	scanf("%d", &tc);
	for (i = tc; i > 0; i--) {
		bFind = false;
		scanf("%d %d", &v_count, &l_count);

		std::vector<int> lineVector[2*MAX_COUNT];

		for (j = 0; j < l_count; j++) {
			scanf("%d ", &temp);
			lineVector[2 * (j + 1)].push_back(temp);
		}

		scanf("%d %d", &start, &target); // 시작 주인공, 목표 지점

		// array에 위치를 기록 (시작점을 기준으로 탐색할 예정)
		index = target;
		for (j = 2*(l_count+1); j > 0; j--) {
			if (!lineVector[j].empty()) {
				data = lineVector[j].at(0);
				if (index == data || index == data + 1)
					index = index > data ? data : data + 1;
			}
			arr[j] = index;
		}

		// 시작점을 기준으로 사다리를 탑니다
		index = start;
		for (j = 2; j < l_count << 1; j++) {
			if (j % 2 == 1) { // 홀수면, 가로 라인 하나를 더 추가할지 말지 결정한다.
				if (index + 1 == arr[j] || index - 1 == arr[j]) {
					bFind = true;
					break;
				}
			}
			else {
				// 위치 만족 시 위치 변경
				data = lineVector[j].at(0);
				if (index == data || index == data + 1)
					index = index > data ? data : data + 1;
			}
		}
		printf("%d\n", bFind == true ? 1 : 0);
	}
	return 0;
}