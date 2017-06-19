#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>
#include <limits.h>

int arrOfRoad[501][501]; 
int distanceRadius[501] = { 0 }; // 도시마다 거리반경의 합
int minOfDistance[501] = { 0 }; // 신하 A의 기준
int sumOfDistance[501] = { 0 }; // 신하 B의 기준
int x[501] = { 0 }; // 신하 C의 기준
bool visited[501] = { false }; // bfs에서 사용할 점을 방문했는지 안했는지
int arrOfPeople[501]; // 도시마다 가지고 있는 인구
int arrOfEdges[501]; // 도시마다 간선의 개수를 기록하는 Array

int main() {
	int testCase, cntOfCapital, cntOfRoad;
	int cap1, cap2;
	int i, j, k; // loop 시 사용할 iterator
	int index = 0; // loop 에서 사용할 index
	int maxOfEdges; // 가장 많이 간선을 가지고 있는 점의 간선의 개수
	int minOfX, result; // 가장 밑 연산 시 사용
	std::queue<int> optQueue; // bfs 시 사용할 Queue
	std::vector<int> vecOfMaxEdges; // 엣지를 가장 많이 가지고 있는 점들을 담는 vector	

	scanf("%d",&testCase);
	for (i = testCase; i > 0; i--) {
		memset(arrOfRoad, 0, sizeof(int) * 501 * 501); // 메모리 초기화 (도시마다 연결되어있는지 안되는지, 연결되면 1, 되어있지 않으면 0)
		memset(arrOfEdges, 0, sizeof(int) * 501); // 메모리 초기화 (간선 관련)
		maxOfEdges = 0; // 도시가 가지고 있는 최대 간선의 개수 0으로 초기화

		scanf("%d %d", &cntOfCapital, &cntOfRoad);
		for (j = 0; j < cntOfCapital; j++) {
			scanf("%d", &arrOfPeople[j]); // 인구 수 입력
		}
		for (j = 0; j < cntOfRoad; j++) {
			scanf("%d %d", &cap1, &cap2);
			arrOfRoad[cap1 - 1][cap2 - 1] = 1;
			arrOfRoad[cap2 - 1][cap1 - 1] = 1;
			arrOfEdges[cap1 - 1]++; // 도시 인덱스에 해당하는 간선의 개수 증가시킴
			arrOfEdges[cap2 - 1]++;
			maxOfEdges = arrOfEdges[cap1 - 1] > maxOfEdges ? arrOfEdges[cap1 - 1] : maxOfEdges; // 최대 간선의 개수 초기화
			maxOfEdges = arrOfEdges[cap2 - 1] > maxOfEdges ? arrOfEdges[cap2 - 1] : maxOfEdges;
		}
		for (j = 0; j < cntOfCapital; j++) {
			if (arrOfEdges[j] == maxOfEdges)
				vecOfMaxEdges.push_back(j); // 간선의 수가 가장 많은 도시만 탐색하도록 한다. (이것이 신하A,신하B,신하C의 공통기준을 만족한다)
		}

		result = -1;
		minOfX = INT_MAX;
		j = 0;

		// 거리별 거리 구하는 과정(Queue를 활용해서 BFS[너비우선탐색])
		while (j < vecOfMaxEdges.size()) {
			index = vecOfMaxEdges.at(j);
			minOfDistance[index] = 0;
			sumOfDistance[index] = 0;
			memset(distanceRadius, 0, sizeof(int) * 501);
			memset(visited, 0, sizeof(bool) * 501);

			optQueue.push(index);
			visited[index] = true;
			while (optQueue.size() > 0) {
				int front = optQueue.front();
				optQueue.pop();
				for (k = 0; k < cntOfCapital; k++) {
					if (arrOfRoad[front][k] > 0) {
						if (!visited[k]) {
							optQueue.push(k);
							visited[k] = true;
							distanceRadius[k] = distanceRadius[front] + 1;
						}
						distanceRadius[k] = distanceRadius[k] > (distanceRadius[front] + 1) ? (distanceRadius[front] + 1) : distanceRadius[k];
					}
				}
			}
			for (k = 0; k < cntOfCapital; k++) {
				minOfDistance[index] = distanceRadius[k] > minOfDistance[index] ? distanceRadius[k] : minOfDistance[index];
				sumOfDistance[index] += distanceRadius[k];
			}
			// 최소 거리 계산 해결
			// 거리합 계산 해결
			// x값 구하기 완료
			x[index] = (cntOfCapital - 1) * minOfDistance[index] + sumOfDistance[index];
			minOfX = x[index] < minOfX ? x[index] : minOfX;
			j++;
		}
		for (j = 0; j < vecOfMaxEdges.size(); j++) {
			if (x[vecOfMaxEdges.at(j)] == minOfX) {
				if (result < 0)
					result = vecOfMaxEdges.at(j) + 1;
				else
					result = arrOfPeople[vecOfMaxEdges.at(j)] > arrOfPeople[result - 1] ? vecOfMaxEdges.at(j) + 1 : result; // 도시마다 x값이 같은 경우에는 인구수 비교로 인구수가 큰 도시를 수도로 선택한다.
			}
		}
		printf("%d\n", result);
	}	
	return 0;
}