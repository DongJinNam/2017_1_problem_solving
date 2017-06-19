#include <stdio.h>
#include <string.h>

#define ORIGIN_MAX 61 // ���� ���� ��ǥ �ִ밪
#define COMPARE_MAX 91 // �� ���� ��ǥ �ִ밪
#define BOARD_MAX 1001 // board x ���� �ִ�, y ���� �ִ�

int xOfOrigin[ORIGIN_MAX];
int yOfOrigin[ORIGIN_MAX];
int xOfCompare[COMPARE_MAX];
int yOfCompare[COMPARE_MAX];
bool boardOfCmp[BOARD_MAX][BOARD_MAX];

int main() {
	int tc, i, j, k;
	int N, M;
	bool bFind = false; // ���߷� 90%�� �Ѵ� case ��� ���������� ����
	int dx, dy;

	scanf("%d", &tc);
	for (tc; tc > 0; tc--) {		
		memset(xOfOrigin, 0, sizeof(int) * ORIGIN_MAX); // ���� ������ x��ǥ ����
		memset(yOfOrigin, 0, sizeof(int) * ORIGIN_MAX); // ���� ������ y��ǥ ����
		memset(xOfCompare, 0, sizeof(int) * COMPARE_MAX); //�� ������ x��ǥ ����
		memset(yOfCompare, 0, sizeof(int) * COMPARE_MAX); //�� ������ y��ǥ ����
		memset(boardOfCmp, 0, sizeof(bool)*BOARD_MAX*BOARD_MAX); // ���� ���� ��ǥ���� board
		scanf("%d", &N); // ���� ���� ����
		for (i = 0; i < N; i++) {
			scanf("%d %d", &xOfOrigin[i], &yOfOrigin[i]);
		}

		scanf("%d", &M); // �� ���� ����
		for (i = 0; i < M; i++) {
			scanf("%d %d", &xOfCompare[i], &yOfCompare[i]);
			boardOfCmp[yOfCompare[i]][xOfCompare[i]] = true;
		}

		int basic = N / 10; // ���� ���� ���� (���� count�� basic ���� ũ�� fail)
		int complete = N - basic; // ���� ���� ����
		int cntOfError = 0; // ����ȸ��

		// new code
		bFind = false; // ��°�.
		for (i = 0; i < basic+1; i++) { // basic + 1�� �� ������, �������� ��������, �����̵� ��ü�� �Ұ����� ���, �ƿ� false�� ����
			for (j = 0; j < M; j++) {
				dx = xOfCompare[j] - xOfOrigin[i]; // ���� x��ǥ - ���� x��ǥ
				dy = yOfCompare[j] - yOfOrigin[i]; // ���� y��ǥ - ���� y��ǥ
				cntOfError = 0;
				for (k = 1; k <= N; k++) {
					if (k > basic && cntOfError > basic) break; // �̹� ���� ������ �ʰ��� ���, loop�� �������´�.
					int indexH = dy + yOfOrigin[k - 1];
					int indexW = dx + xOfOrigin[k - 1];
					if (indexH > 1000 || indexH < 0) {
						cntOfError++; // ���� ������ Area�� ����� ���, ������ �����ؼ� �߰���
						continue;
					}
					if (indexW > 1000 || indexW < 0) {
						cntOfError++; // ���� ������ Area�� ����� ���, ������ �����ؼ� �߰���
						continue;
					}
					if (!boardOfCmp[indexH][indexW])
						cntOfError++; // ���� �̵� �� boardOfCmp�� ���� ��, ������ �����ؼ� �߰���
				}
				if (cntOfError <= basic)
					bFind = true; // ���� Case�� basic (���� Case �� 1/10) ���� �۰ų� ���� ���, Success!
				if (bFind) break;
			}
			if (bFind) break;
		}
		printf("%d\n", bFind == true ? 1 : 0);
	}
	return 0;
}