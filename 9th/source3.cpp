#include <stdio.h>
#include <string.h>

#define ORIGIN_MAX 61 // 기준 지문 좌표 최대값
#define COMPARE_MAX 91 // 비교 지문 좌표 최대값
#define BOARD_MAX 1001 // board x 개수 최대, y 개수 최대

int xOfOrigin[ORIGIN_MAX];
int yOfOrigin[ORIGIN_MAX];
int xOfCompare[COMPARE_MAX];
int yOfCompare[COMPARE_MAX];
bool boardOfCmp[BOARD_MAX][BOARD_MAX];

int main() {
	int tc, i, j, k;
	int N, M;
	bool bFind = false; // 적중률 90%가 넘는 case 경우 빠져나오는 조건
	int dx, dy;

	scanf("%d", &tc);
	for (tc; tc > 0; tc--) {		
		memset(xOfOrigin, 0, sizeof(int) * ORIGIN_MAX); // 기준 지문의 x좌표 모음
		memset(yOfOrigin, 0, sizeof(int) * ORIGIN_MAX); // 기준 지문의 y좌표 모음
		memset(xOfCompare, 0, sizeof(int) * COMPARE_MAX); //비교 지문의 x좌표 모음
		memset(yOfCompare, 0, sizeof(int) * COMPARE_MAX); //비교 지문의 y좌표 모음
		memset(boardOfCmp, 0, sizeof(bool)*BOARD_MAX*BOARD_MAX); // 비교할 지문 좌표들의 board
		scanf("%d", &N); // 기준 지문 개수
		for (i = 0; i < N; i++) {
			scanf("%d %d", &xOfOrigin[i], &yOfOrigin[i]);
		}

		scanf("%d", &M); // 비교 지문 개수
		for (i = 0; i < M; i++) {
			scanf("%d %d", &xOfCompare[i], &yOfCompare[i]);
			boardOfCmp[yOfCompare[i]][xOfCompare[i]] = true;
		}

		int basic = N / 10; // 실패 만족 조건 (에러 count가 basic 보다 크면 fail)
		int complete = N - basic; // 성공 만족 조건
		int cntOfError = 0; // 에러회수

		// new code
		bFind = false; // 출력값.
		for (i = 0; i < basic+1; i++) { // basic + 1로 둔 이유는, 기준점을 기준으로, 평행이동 자체가 불가능한 경우, 아예 false로 판정
			for (j = 0; j < M; j++) {
				dx = xOfCompare[j] - xOfOrigin[i]; // 비교할 x좌표 - 기준 x좌표
				dy = yOfCompare[j] - yOfOrigin[i]; // 비교할 y좌표 - 기준 y좌표
				cntOfError = 0;
				for (k = 1; k <= N; k++) {
					if (k > basic && cntOfError > basic) break; // 이미 에러 개수를 초과한 경우, loop를 빠져나온다.
					int indexH = dy + yOfOrigin[k - 1];
					int indexW = dx + xOfOrigin[k - 1];
					if (indexH > 1000 || indexH < 0) {
						cntOfError++; // 판정 기준이 Area를 벗어나는 경우, 에러로 가정해서 추가함
						continue;
					}
					if (indexW > 1000 || indexW < 0) {
						cntOfError++; // 판정 기준이 Area를 벗어나는 경우, 에러로 가정해서 추가함
						continue;
					}
					if (!boardOfCmp[indexH][indexW])
						cntOfError++; // 평행 이동 시 boardOfCmp에 없을 시, 에러로 가정해서 추가함
				}
				if (cntOfError <= basic)
					bFind = true; // 에러 Case가 basic (기존 Case 중 1/10) 보다 작거나 같은 경우, Success!
				if (bFind) break;
			}
			if (bFind) break;
		}
		printf("%d\n", bFind == true ? 1 : 0);
	}
	return 0;
}