#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string.h>

#define MAX_N 10000
#define MAX_LOC 10000000

using namespace std;

int n, seg[4 * MAX_N], b[MAX_N];
int angle; // 어느 방향인지. 0 : 북, 1 : 북동, 2 : 동, 3 : 남동, 4 : 남, 5 : 남서, 6 : 서, 7 : 북서

pair<int, int> a[MAX_N + 1];

bool cmp(pair<int, int> a, pair<int, int> b) { // compare function
	if (a.first == b.first)
		return a.second > b.second;
	return a.first < b.first;
}

int update(int pos, int val, int node, int x, int y) { // segment tree update function
	if (y < pos || pos < x)
		return seg[node];
	if (x == y)
		return seg[node] = val;
	int mid = (x + y) >> 1;
	return seg[node] = update(pos, val, node * 2, x, mid) + update(pos, val, node * 2 + 1, mid + 1, y);
}

long long query(int lo, int hi, int node, int x, int y) { // 구간합 구하기
	if (y < lo || hi < x)
		return 0;
	if (lo <= x && y <= hi)
		return seg[node];
	int mid = (x + y) >> 1;
	return query(lo, hi, node * 2, x, mid) + query(lo, hi, node * 2 + 1, mid + 1, y);
}

int main() {

	int tc;
	int angle;
	int i, j, k, z;
	int temp = 0;
	int xInput, yInput;
	long long result = 0;

	scanf("%d", &tc);
	for (tc; tc > 0; tc--) {		
		memset(seg, 0, sizeof(seg)); // segment array
		memset(b, 0, sizeof(b));
		
		vector<int> ypos; // y위치를 담는 vector
		unsigned short cnt[MAX_N] = { 0 };
		result = 0;

		scanf("%d", &angle);
		scanf("%d", &n);
		
		if (angle >= 360)
			angle = 0;
		else
			angle = angle / 45;

		for (i = 1; i <= n; i++) {
			scanf("%d%d", &xInput, &yInput);			
			switch (angle)
			{
			case 1:
				xInput = MAX_LOC - xInput;
				break;
			case 2:
				xInput = MAX_LOC - xInput;
				break;
			case 3:
				xInput = MAX_LOC - xInput;
				yInput = MAX_LOC - yInput;
				break;
			case 4:
				yInput = MAX_LOC - yInput;
				temp = xInput;
				xInput = yInput;
				yInput = temp;
				break;
			case 5:
				yInput = MAX_LOC - yInput;
				break;
			case 6:				
				break;
			case 7:
				// 그대로 사용함.
				break;
			case 0:
				temp = xInput;
				xInput = yInput;
				yInput = temp;
				break;
			default:
				break;
			}
			a[i] = { xInput,yInput };
			ypos.push_back(yInput);
		}
			
		sort(a + 1, a + n + 1, cmp); // y축을 기준으로 sort
		
		if (angle % 2 == 0) { 										
			long long answer = 0, same = 1;						
			for (i = n; i >= 2; i--) {
				if (a[i].first == a[i - 1].first)
					same += 1;
				else {
					answer += same * (i + same - 2);
					same = 1;
				}
			}
			answer += same * (same - 1); // last 섬 처리
			result = answer;
		}
		else {			
			sort(ypos.begin(), ypos.end());
			ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());
			for (i = 1; i <= n; i++) {
				z = lower_bound(ypos.begin(), ypos.end(), a[i].second) - ypos.begin();
				result += (long long)query(z, n - 1, 1, 0, n - 1);
				b[z]++;
				update(z, b[z], 1, 0, n - 1);
			}
		}	
		printf("%lld\n", result);
	}
	return 0;
}