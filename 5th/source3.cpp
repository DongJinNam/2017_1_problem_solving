#include <stdio.h>
#include <string.h>

using namespace std;
short singerlink[1001][1001]; // 가수간 연결관계
short cnt[1001];//들어오는 간선 수 각각 가수번호를 인덱스로 해서 저장
short order[1001];//순서 저장

int main() {
	int N, M;//N은 가수 수, M은 PD수
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
			int prev = 0; // 이전 인덱스
			for (int j = 0; j < num; ++j) {
				scanf("%d", &nxt);
				if (singerlink[prev][nxt]) {
					prev = nxt; continue;
				}
				singerlink[prev][nxt] = 1;
				if (j == 0)singerlink[prev][nxt] = 0;//처음엔 사실 연결 된게 아니므로 원래대로
				else cnt[nxt]++;//들어오는 간선 수 증가했으니까
				prev = nxt;
			}
		}

		//위상정렬 가능한 경우
		int i;
		for (i = 1; i <= N; ++i) {
			//진입 간선이 없는 노드 선택 
			bool found = false;
			int nodenum;
			for (int j = 1; j <= N; ++j) {
				if (cnt[j] == 0) {//그중 가장 빠른 노드 선택
					cnt[j] = -1;//제거
					found = true;
					nodenum = j;
					break;
				}
			}
			if (!found)break;
			order[i] = nodenum;//노드 순서 정보 저장
							   //이 노드에서 나가는 간선들 모두 제거
			for (int j = 1; j <= N; ++j) {
				if (singerlink[nodenum][j]) {
					//nodenum에서 출발해 연결된 간선이면 제거
					singerlink[nodenum][j] = 0;
					cnt[j]--;//j로 들어오는 간선 수 하나 감소
				}
			}
		}

		if (i == N + 1) {//길이 N인 것 찾은 경우
			for (int i = 1; i <= N; ++i)printf("%d ", order[i]);
			printf("\n");
		}
		else {//찾기 실패 
			printf("%d\n", 0);
		}
	}

	return 0;
}