#include <stdio.h>
#include <string.h>

using namespace std;
short singerlink[1001][1001]; // ������ �������
short cnt[1001];//������ ���� �� ���� ������ȣ�� �ε����� �ؼ� ����
short order[1001];//���� ����

int main() {
	int N, M;//N�� ���� ��, M�� PD��
	int testCase;

	scanf("%d", &testCase);

	for (testCase; testCase > 0; testCase--) {
		scanf("%d %d", &N, &M);

		memset(cnt, 0, sizeof(short) * 1001);
		memset(order, 0, sizeof(short) * 1001);
		memset(singerlink, 0, sizeof(short) * 1001 * 1001);

		for (int i = 0; i < M; ++i) {
			int num; scanf("%d", &num);
			int nxt;
			int prev = 0; // ���� �ε���
			for (int j = 0; j < num; ++j) {
				scanf("%d", &nxt);
				if (singerlink[prev][nxt]) {
					prev = nxt; continue;
				}
				singerlink[prev][nxt] = 1;
				if (j == 0)singerlink[prev][nxt] = 0;//ó���� ��� ���� �Ȱ� �ƴϹǷ� �������
				else cnt[nxt]++;//������ ���� �� ���������ϱ�
				prev = nxt;
			}
		}

		//�������� ������ ���
		int i;
		for (i = 1; i <= N; ++i) {
			//���� ������ ���� ��� ���� 
			bool found = false;
			int nodenum;
			for (int j = 1; j <= N; ++j) {
				if (cnt[j] == 0) {//���� ���� ���� ��� ����
					cnt[j] = -1;//����
					found = true;
					nodenum = j;
					break;
				}
			}
			if (!found)break;
			order[i] = nodenum;//��� ���� ���� ����
							   //�� ��忡�� ������ ������ ��� ����
			for (int j = 1; j <= N; ++j) {
				if (singerlink[nodenum][j]) {
					//nodenum���� ����� ����� �����̸� ����
					singerlink[nodenum][j] = 0;
					cnt[j]--;//j�� ������ ���� �� �ϳ� ����
				}
			}
		}

		if (i == N + 1) {//���� N�� �� ã�� ���
			for (int i = 1; i <= N; ++i)printf("%d ", order[i]);
			printf("\n");
		}
		else {//ã�� ���� 
			printf("%d\n", 0);
		}
	}

	return 0;
}