#include <stdio.h>

#define MAX 32 // 구간 배열 길이를 32로 설정

int main() {
	int testCase; // 테스트 케이스 개수, loop iterator
	int i, j, test, temp = 0, interval = 0, result = 0, by2 = 1, input; // loop iterator, 2진수 n자리수 구간에서 최소값 - 1, 구간 간격, 결과값, pow(2,n) 대체 변수, 입력값
	int binaryPoint[MAX], decimalPoint[MAX]; // 숫자별 2진수 n자리 수 구간을 구분하기 위해 선언한 배열, 왼쪽과 관련한 10진수 값을 담는 배열 (0,0 + 2,2 + 6,4 + 18,8 + 50, 16 ...)
	int number,location;

	test = 2;
	j = 1;
	by2 = 2;
	// 입력값을 받았을 때, 미리 구간을 설정해놓는다.(0,0+1*2,0+1*2+2*2,0+1*2+2*2+3*4,...) -> arr
	// tempArr -> {0,2,4,8,16,32,64,128,...)	
	binaryPoint[0] = 0;
	decimalPoint[0] = 0;
	while (j < MAX) {
		interval = by2 * (j + 1); // 2진수로 표현할 때 
		binaryPoint[j] = test;
		decimalPoint[j] = by2;
		by2 <<= 1;
		test += interval;
		temp = by2;
		j++;
	}
	scanf("%d", &testCase); // 테스트 케이스 입력
	for (i = testCase; i > 0; i--) {
		scanf("%d", &input);
		result = 0; // 결과값
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