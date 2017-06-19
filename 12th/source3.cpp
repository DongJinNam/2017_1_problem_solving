#include <stdio.h>
#include <algorithm>
#include <string.h>

#define MAX_COUNT 18 // ����� ������ �ִ� 17�̱� ������ �迭 ��, ���� �ִ� ũ�⸦ 18�� �Ͽ����ϴ�.

//unsigned long int arr_catalan[MAX_COUNT];
unsigned long int arr_board[MAX_COUNT][MAX_COUNT];
unsigned long int arr_board2[MAX_COUNT][MAX_COUNT];
unsigned int arr_dept[MAX_COUNT];
//// īŻ�� �� ���ϱ�
//���� : http://wiki.mathnt.net/index.php?title=%EC%B9%B4%ED%83%88%EB%9E%80_%EC%88%98_(Catalan_numbers)
//C0 = 1, C1 = 1, C2 = 2, C3 = 5
//C3 = C0*C2 + C1*C1 + C2*C0 = 5
//C4 = C0*C3 + C1*C2 + C2*C1 + C3*C0 = 5 + 2 + 2 +5 = 14
//Cn = C0*Cn-1 + C1*Cn-2 + C2 * Cn-3 +....+Cn-1*C0
//unsigned long int catalan(unsigned int n) {
//	
//	if (n <= 1) return 1;
//
//	unsigned long int res = 0;
//	int i;
//	for (i = 0; i < n; i++)
//		res += catalan(i)*catalan(n - i - 1);
//	return res;
//}
int main() {
	int tc, i, j, k;
	int n_cnt, depth, level; // node count, minimum depth
	unsigned long int result = 0;

	//for (i = 0; i < MAX_COUNT; i++) {
	//	arr_catalan[i] = catalan(i);		
	//}
	// level current �� level next�� ���� �� �ִ� ����� ���� ��� ���� 2���� �迭
	// level current 2��, level next 3�� �� ��, -> arr_board[3][2] �� ���� ã�´�.
	for (i = 1; i < MAX_COUNT; i++) {
		arr_board[i][1] = 1;
		for (j = 1; j < MAX_COUNT; j++) {
			if (i == 1) {
				arr_board[i][j] = j;
			}
			else {
				if (j > 1) {
					arr_board[i][j] = arr_board[i][j - 1] + arr_board[i - 1][j];
				}
				else {
					arr_board[i][j] = 1;
				}
			}
		}
	}
	// īŻ�� ���� 2���� �迭
	for (i = 0; i < MAX_COUNT; i++) {
		arr_board2[i][1] = 1;
		for (j = 0; j < MAX_COUNT; j++) {
			if (i == 0) {
				arr_board2[i][j] = j+1;
			}
			else {
				if (j >= i) {
					arr_board2[i][j] = arr_board2[i][j - 1] + arr_board2[i - 1][j];
				}
				else {
					arr_board2[i][j] = 0;
				}
			}
		}
	}
	scanf("%d", &tc);
	for (tc; tc > 0; tc--) {
		scanf("%d", &n_cnt); // node count
		scanf("%d", &depth); // ���� depth ũ��

		result = 1; // ��°�
		for (i = 0; i < depth + 1; i++) 
			scanf("%d", &arr_dept[i]);

		for (i = 0; i < depth + 1; i++) {
			n_cnt -= arr_dept[i];
			if (i == depth) { // ���� ���� count �� ������ ���� ���� ����
				if (arr_dept[i] > 1 && n_cnt > 1) {
					result *= (unsigned long int)(arr_board2[n_cnt - 1][n_cnt - 1 + (arr_dept[i] - 1)]);
				}
				else {
					//result *= (unsigned long int)(arr_dept[i] * arr_catalan[n_cnt]);
					if (n_cnt > 0) // ����ó��
						result *= (unsigned long int)(arr_dept[i] * arr_board2[n_cnt-1][n_cnt-1]);
				}
			}
			else {	// ���� ���� count �� ������ ����
				result *= (unsigned long int)(arr_board[arr_dept[i + 1]][arr_dept[i]]);
			}			
		} 		
		printf("%d\n", result);
	}
	return 0;
}