#include <stdio.h>
#include <math.h>
#include <string.h>

int board[100][50001]; // Dynamic Programming ����� Ȱ���ϱ� ���� board�� ����Ѵ�.

int main() {
	int testCase;
	int cntOfCard, sum;
	int i, j, k;
	int digitCount;
	int temp, totalCnt = 0; // �ӽ�, ���� ���� ���� ���� �� Total ��
	int data;
	int count = 0;
	bool bFind = false;
	scanf("%d", &testCase);

	for (testCase; testCase > 0; testCase--) {
		scanf("%d %d", &cntOfCard, &sum);

		// ���� �ʱ�ȭ
		totalCnt = 0;
		digitCount = 0;
		count = 0;
		temp = 0;
		i = 0;
		j = 0;
		k = 0;
		bFind = false;

		// ���� �� ����� 2���� �ڸ����� ���Ѵ�.
		// ex. 19 �� sum�� ���, 2�� 0����, 2�� 1����, 2�� 2����, 2�� 3����, 2�� 4���� �� 5��.
		temp = sum;
		while (temp > 0) {
			temp >>= 1;
			digitCount++;
		}
		
		memset(board, 0, sizeof(int) * 100 * 50001); // �޸� �ʱ�ȭ

		for (i = 0; i < digitCount; i++) {
			if (bFind) break; // ã�� ���. count
			totalCnt += pow(2, i) * cntOfCard;
			if (i == 0) {
				for (j = 1; j <= cntOfCard; j++) {
					board[0][j] = 1;
				}
			}
			else {
				data = pow(2, i);
				for (j = 1; j <= totalCnt; j++) {
					if (bFind) break; // ã�� ���. count
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

						// j�� �������� ����� ���.
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