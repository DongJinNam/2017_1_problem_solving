#include <stdio.h>
#include <string.h>

#define MAP_SIZE 6

bool map[MAP_SIZE + 1][MAP_SIZE + 1];
bool bVisited[MAP_SIZE + 1][MAP_SIZE + 1];

int sizeMap = 0;

int processing(int y, int x, int depth) {
	int i, rtn;
	int max = 0; // 최대 방문할 수 있는 노드의 수
	bool bExplore = false; // 해당 y,x 로부터 동서남북으로 이동가능한지[true] 아니한지[false]

	bVisited[y][x] = true;

	if (x + 1 < sizeMap && y < sizeMap && bVisited[y][x+1] == false && map[y][x+1] == false) { // 동
		rtn = processing(y, x + 1,depth+1);
		max = rtn > max ? rtn : max;
		bExplore = true;
	}

	if (x - 1 >= 0 && y < sizeMap && bVisited[y][x - 1] == false && map[y][x - 1] == false) { // 서
		rtn = processing(y, x - 1, depth + 1);
		max = rtn > max ? rtn : max;
		bExplore = true;
	}

	if (y + 1 < sizeMap && x < sizeMap && bVisited[y + 1][x] == false && map[y + 1][x] == false) { // 남
		rtn = processing(y + 1, x, depth + 1);
		max = rtn > max ? rtn : max;
		bExplore = true;
	}

	if (y - 1 >= 0 && x < sizeMap && bVisited[y - 1][x] == false && map[y - 1][x] == false) { // 북
		rtn = processing(y - 1, x, depth + 1);
		max = rtn > max ? rtn : max;
		bExplore = true;
	}

	if (!bExplore) { // 더 이상 탐색 불가
		bVisited[y][x] = false; // 탐색 완료한 경우. 방문한 노드에 대해서 bVisited -> false 로 처리
		return depth + 1;
	}
	else {
		// 한번이라도 동서남북 방향으로 탐색에 성공한 경우
		bVisited[y][x] = false; // 탐색 완료한 경우. 방문한 노드에 대해서 bVisited -> false 로 처리
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
		scanf("%d %d", &sizeMap, &cntOfPos); // sizeMap -> N, cntOfPos : 시작 위치 개수
		for (i = 0; i < sizeMap; i++) {
			for (j = 0; j < sizeMap; j++) {
				scanf("%d", &temp);
				map[i][j] = temp > 0 ? true : false; // temp == 1 장애물, temp == 0 평지
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