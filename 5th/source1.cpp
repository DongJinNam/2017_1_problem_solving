#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>
#include <limits.h>

int arrOfRoad[501][501]; 
int distanceRadius[501] = { 0 }; // ���ø��� �Ÿ��ݰ��� ��
int minOfDistance[501] = { 0 }; // ���� A�� ����
int sumOfDistance[501] = { 0 }; // ���� B�� ����
int x[501] = { 0 }; // ���� C�� ����
bool visited[501] = { false }; // bfs���� ����� ���� �湮�ߴ��� ���ߴ���
int arrOfPeople[501]; // ���ø��� ������ �ִ� �α�
int arrOfEdges[501]; // ���ø��� ������ ������ ����ϴ� Array

int main() {
	int testCase, cntOfCapital, cntOfRoad;
	int cap1, cap2;
	int i, j, k; // loop �� ����� iterator
	int index = 0; // loop ���� ����� index
	int maxOfEdges; // ���� ���� ������ ������ �ִ� ���� ������ ����
	int minOfX, result; // ���� �� ���� �� ���
	std::queue<int> optQueue; // bfs �� ����� Queue
	std::vector<int> vecOfMaxEdges; // ������ ���� ���� ������ �ִ� ������ ��� vector	

	scanf("%d",&testCase);
	for (i = testCase; i > 0; i--) {
		memset(arrOfRoad, 0, sizeof(int) * 501 * 501); // �޸� �ʱ�ȭ (���ø��� ����Ǿ��ִ��� �ȵǴ���, ����Ǹ� 1, �Ǿ����� ������ 0)
		memset(arrOfEdges, 0, sizeof(int) * 501); // �޸� �ʱ�ȭ (���� ����)
		maxOfEdges = 0; // ���ð� ������ �ִ� �ִ� ������ ���� 0���� �ʱ�ȭ

		scanf("%d %d", &cntOfCapital, &cntOfRoad);
		for (j = 0; j < cntOfCapital; j++) {
			scanf("%d", &arrOfPeople[j]); // �α� �� �Է�
		}
		for (j = 0; j < cntOfRoad; j++) {
			scanf("%d %d", &cap1, &cap2);
			arrOfRoad[cap1 - 1][cap2 - 1] = 1;
			arrOfRoad[cap2 - 1][cap1 - 1] = 1;
			arrOfEdges[cap1 - 1]++; // ���� �ε����� �ش��ϴ� ������ ���� ������Ŵ
			arrOfEdges[cap2 - 1]++;
			maxOfEdges = arrOfEdges[cap1 - 1] > maxOfEdges ? arrOfEdges[cap1 - 1] : maxOfEdges; // �ִ� ������ ���� �ʱ�ȭ
			maxOfEdges = arrOfEdges[cap2 - 1] > maxOfEdges ? arrOfEdges[cap2 - 1] : maxOfEdges;
		}
		for (j = 0; j < cntOfCapital; j++) {
			if (arrOfEdges[j] == maxOfEdges)
				vecOfMaxEdges.push_back(j); // ������ ���� ���� ���� ���ø� Ž���ϵ��� �Ѵ�. (�̰��� ����A,����B,����C�� ��������� �����Ѵ�)
		}

		result = -1;
		minOfX = INT_MAX;
		j = 0;

		// �Ÿ��� �Ÿ� ���ϴ� ����(Queue�� Ȱ���ؼ� BFS[�ʺ�켱Ž��])
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
			// �ּ� �Ÿ� ��� �ذ�
			// �Ÿ��� ��� �ذ�
			// x�� ���ϱ� �Ϸ�
			x[index] = (cntOfCapital - 1) * minOfDistance[index] + sumOfDistance[index];
			minOfX = x[index] < minOfX ? x[index] : minOfX;
			j++;
		}
		for (j = 0; j < vecOfMaxEdges.size(); j++) {
			if (x[vecOfMaxEdges.at(j)] == minOfX) {
				if (result < 0)
					result = vecOfMaxEdges.at(j) + 1;
				else
					result = arrOfPeople[vecOfMaxEdges.at(j)] > arrOfPeople[result - 1] ? vecOfMaxEdges.at(j) + 1 : result; // ���ø��� x���� ���� ��쿡�� �α��� �񱳷� �α����� ū ���ø� ������ �����Ѵ�.
			}
		}
		printf("%d\n", result);
	}	
	return 0;
}