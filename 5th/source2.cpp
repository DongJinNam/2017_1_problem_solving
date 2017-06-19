#include <stdio.h>
#include <stack>
#include <math.h>
#include <time.h>

std::stack<int> test1, test2, test3; // 3���� ����� �������� ����Ѵ�
int cntOfChange = 0; // �̵��� Ƚ��
int dstOfChange = 0;  // ��ǥ �̵� Ƚ��
int arrOfCntRing[10]; // �� ���ں��� ���� ����� ����. (1 ������ �� ������ 0��, 2 ������ �� ������ 1�� ����)

// from stack���� ������ �ϳ��� pop�ؼ�, to stack�� ������ �ϳ��� push �Ѵ�.
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
	cntOfChange++; // �̵� ������ �Ͽ��� ������, ī��Ʈ�� ������Ų��.
}

void moveData(int from, int to) {
	int fromData, toData; //from stack���� ���� �����Ͱ�, to stack���� ���� �����Ͱ� (stack�� �����Ͱ� ���� �ÿ��� -1�� �ֵ��� �Ѵ�)
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
			// arrOfCntRing �迭�� �ִ� ���� Ȱ���ؼ�, �� ���� �̵��ϵ��� �Ѵ�. �׸��� �̵� Ƚ���� ��ǥġ�� �����ϸ� ���´�.
			while (j++ < arrOfCntRing[toData - 1] && cntOfChange < dstOfChange) { 
				processing(to, from);
			}
		}
		else if (toData == -1){
			// arrOfCntRing �迭�� �ִ� ���� Ȱ���ؼ�, �� ���� �̵��ϵ��� �Ѵ�. �׸��� �̵� Ƚ���� ��ǥġ�� �����ϸ� ���´�.
			while (j++ < arrOfCntRing[fromData - 1] && cntOfChange < dstOfChange) {
				processing(from, to);
			}
		}
		else return;
	}
	else {
		if (fromData < toData) {
			// arrOfCntRing �迭�� �ִ� ���� Ȱ���ؼ�, �� ���� �̵��ϵ��� �Ѵ�. �׸��� �̵� Ƚ���� ��ǥġ�� �����ϸ� ���´�.
			while (j++ < arrOfCntRing[fromData - 1] && cntOfChange < dstOfChange) {
				processing(from, to);
			}
		}
		else if (fromData == toData) {
			// ����ó��
		}
		else {
			// arrOfCntRing �迭�� �ִ� ���� Ȱ���ؼ�, �� ���� �̵��ϵ��� �Ѵ�. �׸��� �̵� Ƚ���� ��ǥġ�� �����ϸ� ���´�.
			while (j++ < arrOfCntRing[toData - 1] && cntOfChange < dstOfChange) {
				processing(to, from);
			}
		}
	}

}

int main() {
	int testCase, cntOfRound; // �׽�Ʈ ���̽� ����, �� ������ ���� ����
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
		// logic ���� ��
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