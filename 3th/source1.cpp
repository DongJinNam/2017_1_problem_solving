#include <stdio.h>

#define MAX 32 // ���� �迭 ���̸� 32�� ����

int main() {
	int testCase; // �׽�Ʈ ���̽� ����, loop iterator
	int i, j, test, temp = 0, interval = 0, result = 0, by2 = 1, input; // loop iterator, 2���� n�ڸ��� �������� �ּҰ� - 1, ���� ����, �����, pow(2,n) ��ü ����, �Է°�
	int binaryPoint[MAX], decimalPoint[MAX]; // ���ں� 2���� n�ڸ� �� ������ �����ϱ� ���� ������ �迭, ���ʰ� ������ 10���� ���� ��� �迭 (0,0 + 2,2 + 6,4 + 18,8 + 50, 16 ...)
	int number,location;

	test = 2;
	j = 1;
	by2 = 2;
	// �Է°��� �޾��� ��, �̸� ������ �����س��´�.(0,0+1*2,0+1*2+2*2,0+1*2+2*2+3*4,...) -> arr
	// tempArr -> {0,2,4,8,16,32,64,128,...)	
	binaryPoint[0] = 0;
	decimalPoint[0] = 0;
	while (j < MAX) {
		interval = by2 * (j + 1); // 2������ ǥ���� �� 
		binaryPoint[j] = test;
		decimalPoint[j] = by2;
		by2 <<= 1;
		test += interval;
		temp = by2;
		j++;
	}
	scanf("%d", &testCase); // �׽�Ʈ ���̽� �Է�
	for (i = testCase; i > 0; i--) {
		scanf("%d", &input);
		result = 0; // �����
		for (j = 0; j < MAX; j++) {
			if (input < binaryPoint[j + 1]) {
				location = binaryPoint[j];
				number = decimalPoint[j];
				break;
			}
		}
		j++;
		if ((input - location) % j == 0) {
			location += ((input - location) / j) * j;
			number += (input - binaryPoint[j-1]) / j;
		}
		else {
			location += ((input - location) / j + 1) * j;
			number += (input - binaryPoint[j - 1]) / j + 1;
		}
		number--;
		location++;
		j = 0;
		result = number & (1 << (location - input - 1));
		if (result == 0) printf("%d\n", 0);
		else printf("%d\n", 1);
	}
	return 0;
}