#include <stdio.h>
#include <stack>
#include <math.h>
#include <time.h>

std::stack<int> test1, test2, test3; // 3가지 기둥을 스택으로 사용한다
int cntOfChange = 0; // 이동한 횟수
int dstOfChange = 0;  // 목표 이동 횟수
int arrOfCntRing[10]; // 링 숫자별로 개수 몇개인지 저장. (1 사이즈 링 개수는 0에, 2 사이즈 링 개수는 1에 등등등)

// from stack에서 데이터 하나를 pop해서, to stack에 데이터 하나를 push 한다.
void processing(int from, int to) {
	int data;
	switch (from) {
	case 1:
		data = test1.top();
		test1.pop();
		break;
	case 2:
		data = test2.top();
		test2.pop();
		break;
	case 3:
		data = test3.top();
		test3.pop();
		break;
	}
	switch (to) {
	case 1:
		test1.push(data);
		break;
	case 2:
		test2.push(data);
		break;
	case 3:
		test3.push(data);
		break;
	}
	cntOfChange++; // 이동 연산을 하였기 때문에, 카운트를 증가시킨다.
}

void moveData(int from, int to) {
	int fromData, toData; //from stack에서 얻을 데이터값, to stack에서 얻을 데이터값 (stack에 데이터가 없을 시에는 -1을 넣도록 한다)
	int j = 0; // loop iterator
	switch (from) {
	case 1:
		if (test1.size() == 0) fromData = -1;
		else fromData = test1.top();
		break;
	case 2:
		if (test2.size() == 0) fromData = -1;
		else fromData = test2.top();
		break;
	case 3:
		if (test3.size() == 0) fromData = -1;
		else fromData = test3.top();
		break;
	}
	switch (to) {
	case 1:
		if (test1.size() == 0) toData = -1;
		else toData = test1.top();
		break;
	case 2:
		if (test2.size() == 0) toData = -1;
		else toData = test2.top();
		break;
	case 3:
		if (test3.size() == 0) toData = -1;
		else toData = test3.top();
		break;
	}
	if (fromData == -1 || toData == -1) {
		if (fromData == -1) {
			// arrOfCntRing 배열에 있는 값을 활용해서, 몇 번씩 이동하도록 한다. 그리고 이동 횟수가 목표치에 도달하면 나온다.
			while (j++ < arrOfCntRing[toData - 1] && cntOfChange < dstOfChange) { 
				processing(to, from);
			}
		}
		else if (toData == -1){
			// arrOfCntRing 배열에 있는 값을 활용해서, 몇 번씩 이동하도록 한다. 그리고 이동 횟수가 목표치에 도달하면 나온다.
			while (j++ < arrOfCntRing[fromData - 1] && cntOfChange < dstOfChange) {
				processing(from, to);
			}
		}
		else return;
	}
	else {
		if (fromData < toData) {
			// arrOfCntRing 배열에 있는 값을 활용해서, 몇 번씩 이동하도록 한다. 그리고 이동 횟수가 목표치에 도달하면 나온다.
			while (j++ < arrOfCntRing[fromData - 1] && cntOfChange < dstOfChange) {
				processing(from, to);
			}
		}
		else if (fromData == toData) {
			// 예외처리
		}
		else {
			// arrOfCntRing 배열에 있는 값을 활용해서, 몇 번씩 이동하도록 한다. 그리고 이동 횟수가 목표치에 도달하면 나온다.
			while (j++ < arrOfCntRing[toData - 1] && cntOfChange < dstOfChange) {
				processing(to, from);
			}
		}
	}

}

int main() {
	int testCase, cntOfRound; // 테스트 케이스 개수, 링 사이즈 개수 종류
	int i, j, k, data;	

	clock_t begin, end;

	scanf("%d", &testCase);
	begin = clock();
	for (i = testCase; i > 0; i--) {
		scanf("%d", &cntOfRound);
		for (j = 0; j < cntOfRound; j++) {
			scanf("%d", &arrOfCntRing[j]);
		}
		for (j = cntOfRound - 1; j >= 0; j--) {
			for (k = 1; k <= arrOfCntRing[j]; k++) {
				test1.push(j + 1);
			}
		}
		scanf("%d", &dstOfChange);
		// logic setting
		int a = 1, b = 2, c = 3;
		if (cntOfRound % 2 == 0) {
			b = 3;
			c = 2;
		}
		cntOfChange = 0;
		j = 1;
		while (cntOfChange < dstOfChange) {
			switch (j % 3) {
			case 0:
				moveData(b, c);
				break;
			case 1:
				moveData(a, c);
				break;
			case 2:
				moveData(a, b);
				break;
			}
			j++;
		}
		// logic 구현 끝
		if (test2.size() > 0) {
			while (test2.size() > 1) {
				data = test2.top();
				test2.pop();
				printf("%d ", data);
			}
			data = test2.top();
			test2.pop();
			printf("%d\n", data);
		}
		else {
			printf("%d\n", 0);
		}

		while (test1.size() > 0)
			test1.pop();
		while (test2.size() > 0)
			test2.pop();
		while (test3.size() > 0)
			test3.pop();
	}
	end = clock();
	//printf("%d seconds\n", ((end - begin) / CLOCKS_PER_SEC));
	return 0;
}