#include <stdio.h>
#include <math.h>
#include <string.h>

int board[100][50001]; // Dynamic Programming 기법을 활용하기 위해 board를 사용한다.

int main() {
	int testCase;
	int cntOfCard, sum;
	int i, j, k;
	int digitCount;
	int temp, totalCnt = 0; // 임시, 내장 루프 내에 루프 총 Total 수
	int data;
	int count = 0;
	bool bFind = false;
	scanf("%d", &testCase);

	for (testCase; testCase > 0; testCase--) {
		scanf("%d %d", &cntOfCard, &sum);

		// 변수 초기화
		totalCnt = 0;
		digitCount = 0;
		count = 0;
		temp = 0;
		i = 0;
		j = 0;
		k = 0;
		bFind = false;

		// 연산 시 사용할 2진수 자리수를 구한다.
		// ex. 19 가 sum인 경우, 2의 0제곱, 2의 1제곱, 2의 2제곱, 2의 3제곱, 2의 4제곱 총 5개.
		temp = sum;
		while (temp > 0) {
			temp >>= 1;
			digitCount++;
		}
		
		memset(board, 0, sizeof(int) * 100 * 50001); // 메모리 초기화

		for (i = 0; i < digitCount; i++) {
			if (bFind) break; // 찾은 경우. count
			totalCnt += pow(2, i) * cntOfCard;
			if (i == 0) {
				for (j = 1; j <= cntOfCard; j++) {
					board[0][j] = 1;
				}
			}
			else {
				data = pow(2, i);
				for (j = 1; j <= totalCnt; j++) {
					if (bFind) break; // 찾은 경우. count
					if (j < data) {
						board[i][j] = board[i - 1][j];
					}
					else {
						if (j % data == 0) {
							if (j <= data * cntOfCard)
								board[i][j] = board[i - 1][j] > 0 ? board[i - 1][j] + 1 : 1;
							else
								board[i][j] == 0;
						}
						else {
							board[i][j] = board[i - 1][j] > 0 ? board[i - 1][j] : 0;
						}

						// j가 영역밖을 벗어나는 경우.
						if (j > data*cntOfCard) 
							k = cntOfCard;						
						else
							k = j / data;

						for (k; k > 0; k--) {
							temp = j - k * data;
							if (board[i - 1][temp] > 0)
								board[i][j] += board[i - 1][temp];
							else
								continue;
						}
						if (i == digitCount - 1 && j == sum) {
							bFind = true;
							count = board[i][j];
						}
					}
				}
			}
		}	
		printf("%d\n", count);
	}	
	return 0;
}