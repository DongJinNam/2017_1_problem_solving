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
	int tc, i, j, k, temp, capOfMax; // �׽�Ʈ ���̽�, ���� iterator, �ӽð�, ���� ���� ���� ��, ���� ���� ���� ���� ��ȣ
	int cntOfCap, cntOfRoad;
	int maxOfEdges, maxIndex;
	int data1, data2;
	unsigned long long max = 0; // ����� �ִ밪
	unsigned long long totalCars = 0; // ��ü �ڵ��� ����
	unsigned long long totalParks = 0; // ��ü ���̰��� ����
	unsigned long long car1 = 0, car2 = 0; // 1�׷쿡 �ִ� car ����, 2�׷쿡 �ִ� car ����
	unsigned long long park1 = 0, park2 = 0; // 1�׷쿡 �ִ� park ����, 2�׷쿡 �ִ� park ����
	unsigned long long result1 = 0, result2 = 0; // 1�׷� ���, 2�׷� ���

	scanf("%d", &tc);
	for (tc; tc > 0; tc--) {
		scanf("%d %d", &cntOfCap, &cntOfRoad); // ���� ����, ���� ����
		memset(arrOfCars, 0, sizeof(int) * MAX_COUNT);
		memset(arrOfParks, 0, sizeof(int) * MAX_COUNT);		

		totalCars = 0; // �ʱⰪ 0����
		totalParks = 0; // �ʱⰪ 0����

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
			temp = data1 * 10000 + data2; // start , to �� �����ϱ� ���ؼ� �Ʒ��� ���� �����Ѵ�.
			vecOfMap[data1].push_back(data2);
			vecOfMap[data2].push_back(data1);
			arrOfMap.insert(std::pair<int, unsigned long>(temp,0));
		}

		max = 0; // ����� ��� �ִ밪
		std::queue<int> optQueue;

		//edge (start,to) �� ������� edge trafiic�� map���� �����ϰ�, 
		for (mapIt = arrOfMap.begin(); mapIt != arrOfMap.end(); mapIt++) {
			int start, to;
			start = mapIt->first / 10000; // ������
			to = mapIt->first % 10000; // �� ��

			memset(bVisited, false, sizeof(bool)*MAX_COUNT); // �޸� �ʱ�ȭ

			// start - to edge �� ������ �ִٰ� �����ϰ�, start ���� �������� bfs�� ������, �ش� �׷��� ���� �� ���� ��尡 �ִ��� bVisited[i] = true �� üũ
			bVisited[start] = true;
			bVisited[to] = true; 
			optQueue.push(start);

			//�׷����� 2�׷����� ������.
			//why?
			//���������� edge�� ���ؼ�, ���̰����� ���ϴ� ������ ���� ���� ������ 2����.
			//A->B (A �׷쿡 �ִ� ������ B �׷쿡 �ִ� ���̰����� �湮), A<-B (B �׷쿡 �ִ� ������ A �׷쿡 �ִ� ���̰����� �湮)
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
			bVisited[to] = false; // edge�� ����� ������ to ���� 1�׷��� �ƴϱ� ������ false�� ó��

			car1 = 0; 
			car2 = 0; // 1�׷쿡 �ִ� car ����, 2�׷쿡 �ִ� car ����
			park1 = 0; 
			park2 = 0; // 1�׷쿡 �ִ� park ����, 2�׷쿡 �ִ� park ����
			result1 = 0; 
			result2 = 0; // 1�׷� ���, 2�׷� ���
			for (i = 1; i <= cntOfCap; i++) {
				if (bVisited[i]) {
					car1 += arrOfCars[i];
					park1 += arrOfParks[i];
				}
			}
			// ��ü���� 1�׷� ����� ����
			car2 = totalCars - car1; 
			park2 = totalParks - park1;
			result1 = car1 * park2; // 1�׷쿡 �ִ� �ڵ������� 2�׷쿡 �ִ� ���̰����� �湮�ϴ� �� ����
			result2 = car2 * park1; // 2�׷쿡 �ִ� �ڵ������� 1�׷쿡 �ִ� ���̰����� �湮�ϴ� �� ����
			mapIt->second = result1 + result2; // edge ���� ����
			max = mapIt->second > max ? mapIt->second : max;
		}
		printf("%llu\n", max);		
	}
	return 0;
}