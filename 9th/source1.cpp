#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
#include <map>

#define MAX_COUNT 5001

int arrOfCars[MAX_COUNT];
int arrOfParks[MAX_COUNT];
bool bVisited[MAX_COUNT];

int main() {
	int tc, i, j, k, temp, capOfMax; // 테스트 케이스, 루프 iterator, 임시값, 간선 가장 많은 값, 간선 가장 많은 도시 번호
	int cntOfCap, cntOfRoad;
	int maxOfEdges, maxIndex;
	int data1, data2;
	unsigned long long max = 0; // 출력할 최대값
	unsigned long long totalCars = 0; // 전체 자동차 개수
	unsigned long long totalParks = 0; // 전체 놀이공원 개수
	unsigned long long car1 = 0, car2 = 0; // 1그룹에 있는 car 개수, 2그룹에 있는 car 개수
	unsigned long long park1 = 0, park2 = 0; // 1그룹에 있는 park 개수, 2그룹에 있는 park 개수
	unsigned long long result1 = 0, result2 = 0; // 1그룹 결과, 2그룹 결과

	scanf("%d", &tc);
	for (tc; tc > 0; tc--) {
		scanf("%d %d", &cntOfCap, &cntOfRoad); // 도시 개수, 도로 개수
		memset(arrOfCars, 0, sizeof(int) * MAX_COUNT);
		memset(arrOfParks, 0, sizeof(int) * MAX_COUNT);		

		totalCars = 0; // 초기값 0으로
		totalParks = 0; // 초기값 0으로

		std::map<int, unsigned long long> arrOfMap;
		std::map<int, unsigned long long>::iterator mapIt;
		std::vector<int> vecOfMap[MAX_COUNT];

		for (i = 1; i <= cntOfCap; i++) {
			scanf("%d %d", &arrOfCars[i], &arrOfParks[i]);
			totalCars += arrOfCars[i];
			totalParks += arrOfParks[i];
		}
		for (i = 1; i <= cntOfRoad; i++) {
			scanf("%d %d", &data1, &data2);
			temp = data1 * 10000 + data2; // start , to 를 구분하기 위해서 아래와 같이 저장한다.
			vecOfMap[data1].push_back(data2);
			vecOfMap[data2].push_back(data1);
			arrOfMap.insert(std::pair<int, unsigned long>(temp,0));
		}

		max = 0; // 출력할 결과 최대값
		std::queue<int> optQueue;

		//edge (start,to) 점 정보들과 edge trafiic을 map으로 관리하고, 
		for (mapIt = arrOfMap.begin(); mapIt != arrOfMap.end(); mapIt++) {
			int start, to;
			start = mapIt->first / 10000; // 시작점
			to = mapIt->first % 10000; // 끝 점

			memset(bVisited, false, sizeof(bool)*MAX_COUNT); // 메모리 초기화

			// start - to edge 가 끊어져 있다고 가정하고, start 점을 기준으로 bfs를 돌려서, 해당 그래프 내에 몇 개의 노드가 있는지 bVisited[i] = true 로 체크
			bVisited[start] = true;
			bVisited[to] = true; 
			optQueue.push(start);

			//그래프를 2그룹으로 나눈다.
			//why?
			//최종적으로 edge를 통해서, 놀이공원을 향하는 차량의 개수 측정 기준이 2가지.
			//A->B (A 그룹에 있는 차들이 B 그룹에 있는 놀이공원을 방문), A<-B (B 그룹에 있는 차들이 A 그룹에 있는 놀이공원을 방문)
			// bfs
			while (!optQueue.empty()) {
				int index = optQueue.front();
				int next = index;
				optQueue.pop();
				bVisited[index] = true;
				for (k = 0; k < vecOfMap[index].size(); k++) {
					int at = vecOfMap[index].at(k);
					if (!bVisited[at]) {
						bVisited[at] = true;
						optQueue.push(at);
					}
				}
			}
			bVisited[to] = false; // edge와 연결된 목적지 to 노드는 1그룹이 아니기 때문에 false로 처리

			car1 = 0; 
			car2 = 0; // 1그룹에 있는 car 개수, 2그룹에 있는 car 개수
			park1 = 0; 
			park2 = 0; // 1그룹에 있는 park 개수, 2그룹에 있는 park 개수
			result1 = 0; 
			result2 = 0; // 1그룹 결과, 2그룹 결과
			for (i = 1; i <= cntOfCap; i++) {
				if (bVisited[i]) {
					car1 += arrOfCars[i];
					park1 += arrOfParks[i];
				}
			}
			// 전체에서 1그룹 결과를 뺀것
			car2 = totalCars - car1; 
			park2 = totalParks - park1;
			result1 = car1 * park2; // 1그룹에 있는 자동차들이 2그룹에 있는 놀이공원에 방문하는 총 개수
			result2 = car2 * park1; // 2그룹에 있는 자동차들이 1그룹에 있는 놀이공원에 방문하는 총 개수
			mapIt->second = result1 + result2; // edge 별로 저장
			max = mapIt->second > max ? mapIt->second : max;
		}
		printf("%llu\n", max);		
	}
	return 0;
}