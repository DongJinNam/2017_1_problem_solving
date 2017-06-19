#include <stdio.h>
#include <string.h>

#define MAP_SIZE 6

bool map[MAP_SIZE + 1][MAP_SIZE + 1];
bool bVisited[MAP_SIZE + 1][MAP_SIZE + 1];

int sizeMap = 0;

int processing(int y, int x, int depth) {
	int i, rtn;
	int max = 0; // �ִ� �湮�� �� �ִ� ����� ��
	bool bExplore = false; // �ش� y,x �κ��� ������������ �̵���������[true] �ƴ�����[false]

	bVisited[y][x] = true;

	if (x + 1 < sizeMap && y < sizeMap && bVisited[y][x+1] == false && map[y][x+1] == false) { // ��
		rtn = processing(y, x + 1,depth+1);
		max = rtn > max ? rtn : max;
		bExplore = true;
	}

	if (x - 1 >= 0 && y < sizeMap && bVisited[y][x - 1] == false && map[y][x - 1] == false) { // ��
		rtn = processing(y, x - 1, depth + 1);
		max = rtn > max ? rtn : max;
		bExplore = true;
	}

	if (y + 1 < sizeMap && x < sizeMap && bVisited[y + 1][x] == false && map[y + 1][x] == false) { // ��
		rtn = processing(y + 1, x, depth + 1);
		max = rtn > max ? rtn : max;
		bExplore = true;
	}

	if (y - 1 >= 0 && x < sizeMap && bVisited[y - 1][x] == false && map[y - 1][x] == false) { // ��
		rtn = processing(y - 1, x, depth + 1);
		max = rtn > max ? rtn : max;
		bExplore = true;
	}

	if (!bExplore) { // �� �̻� Ž�� �Ұ�
		bVisited[y][x] = false; // Ž�� �Ϸ��� ���. �湮�� ��忡 ���ؼ� bVisited -> false �� ó��
		return depth + 1;
	}
	else {
		// �ѹ��̶� �������� �������� Ž���� ������ ���
		bVisited[y][x] = false; // Ž�� �Ϸ��� ���. �湮�� ��忡 ���ؼ� bVisited -> false �� ó��
		return max;
	}
}

int main() {
	int tc;
	int i, j, k;
	int cntOfPos;
	int temp;
	int startX, startY, rtn;

	scanf("%d", &tc);
	for (tc; tc > 0; tc--) {
		scanf("%d %d", &sizeMap, &cntOfPos); // sizeMap -> N, cntOfPos : ���� ��ġ ����
		for (i = 0; i < sizeMap; i++) {
			for (j = 0; j < sizeMap; j++) {
				scanf("%d", &temp);
				map[i][j] = temp > 0 ? true : false; // temp == 1 ��ֹ�, temp == 0 ����
			}
		}
		for (cntOfPos; cntOfPos > 0; cntOfPos--) {
			scanf("%d %d", &startY, &startX);
			memset(bVisited, false, sizeof(bool)*(MAP_SIZE + 1)*(MAP_SIZE + 1));
			rtn = processing(startY, startX, 0);
			printf("%d\n", rtn);
		}		
	}
	return 0;
}