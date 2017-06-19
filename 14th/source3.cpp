#include <stdio.h>
#include <string.h>

#define DIGIT 10

// 행 : src, 열 : dst (src 숫자로부터 dst 숫자로 바꾸는데에 필요한 segment 개수)
int board[DIGIT][DIGIT] = {
	0,4,3,3,4,3,2,3,1,2,
	4,0,5,3,2,5,6,1,5,4,
	3,5,0,2,5,4,3,4,2,3,
	3,3,2,0,3,2,3,2,2,1,
	4,2,5,3,0,3,4,3,3,2,
	3,5,4,2,3,0,1,4,2,1,
	2,6,3,3,4,1,0,5,1,2,
	3,1,4,2,3,4,5,0,4,3,
	1,5,2,2,3,2,1,4,0,1,
	2,4,3,1,2,1,2,3,1,0
};

int digitArr[30]; // 입력 숫자열
int resultArr[30]; // 출력 숫자열

// 가장 큰 숫자를 찾기 위한 재귀함수
int processing(int temp, int index) {
	int i, rtn = -1;
	bool bFind = false;

	if (temp == 0) { // 처리할 세그먼트 개수가 0이므로, 이 경우 가장 큰 숫자를 찾았다는 의미
		return digitArr[index];
	}

	if (index == 0) { // 마지막 index
		for (i = DIGIT - 1; i >= 0; i--) {
			if (temp >= board[digitArr[index]][i]) {
				temp -= board[digitArr[index]][i];
				if (temp == 0) {
					bFind = true;
					break;
				}
				else
					temp += board[digitArr[index]][i]; // 오류 발생 경우, temp 값 원상 복구				
			}
		}
	}
	else {
		for (i = DIGIT - 1; i >= 0; i--) {
			if (temp >= board[digitArr[index]][i]) {				
				temp -= board[digitArr[index]][i];				
				rtn = processing(temp, index - 1);
				if (rtn != -1) {
					bFind = true; // 큰 숫자를 찾았다는 의미
					resultArr[index - 1] = rtn; // 오른쪽으로부터 (index-1) 위치의 값을 processing 함수의 return 값으로 설정
					break;
				}
				else
					temp += board[digitArr[index]][i]; // 오류 발생 경우, temp 값 원상 복구
			}
		}
	}	
	if (!bFind) // 남아있는 세그먼트가 발생했거나, 세그먼트를 초과해서 사용할 시 -1을 리턴함으로써 오류임을 calling function에게 알려준다.
		return -1;
	else
		return i;
}

int main() {
	int tc;
	int i, j, k;
	int cntSegment,cntToChange; // 예정 세그먼트 개수,
	int temp,index;

	scanf("%d", &tc);
	for (tc; tc > 0; tc--) {
		scanf("%d", &cntSegment);
		temp = cntSegment - 1;
		while (temp >= 0) {
			char input;
			input = getchar();

			if (input < '0' || input > '9')
				continue;

			digitArr[temp] = (int)(input - '0');
			resultArr[temp] = digitArr[temp];
			temp--;
		}
		scanf("%d", &cntToChange);
		
		temp = cntToChange;
		index = cntSegment - 1;

		int rtn;
		rtn = processing(temp, index);
		resultArr[index] = rtn;

		for (i = cntSegment - 1; i >= 0; i--) {
			printf("%d", resultArr[i]);
		}
		printf("\n");
	}
	return 0;
}