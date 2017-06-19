#include <stdio.h>
#include <iostream>

int main() {
	int testCase, i, j, k, cntOfArray, cntOfSort, max = 0;
	int arr[300];
	scanf("%d", &testCase);
	for (i = 0; i < testCase; i++) {
		scanf("%d", &cntOfArray);
		for (j = cntOfArray; j > 0; j--) {
			scanf("%d", &arr[j - 1]);
		}
		// sorting
		cntOfSort = 0;
		j = 0;
		int top = 0;
		for (k = 0; k < cntOfArray - top; k++) {
			max = arr[k] > max ? arr[k] : max;
		}
		while (top + 1 < cntOfArray) {
			if (j >= cntOfArray) j = 0;
			if (arr[j] == max) {
				if (j == cntOfArray - 1 - top) {
					top++;
					max = arr[0];
					for (k = 0; k < cntOfArray - top; k++) {
						max = arr[k] > max ? arr[k] : max;
					}
					continue;
				}
				else if (j > 0) {
					for (k = 0; k < (j+1) >> 1; k++) {
						std::swap(arr[k], arr[j - k]);
					}
					cntOfSort++;
				}
			}
			if (arr[0] == max) {
				for (k = 0; k < (cntOfArray - top) >> 1; k++) {
					std::swap(arr[k], arr[cntOfArray - 1 - top - k]);
				}
				cntOfSort++;
				top++;
				max = arr[0];
				for (k = 0; k < cntOfArray - top; k++) {
					max = arr[k] > max ? arr[k] : max;
				}
				j = 0;
				continue;
			}
			j++;
		}
		printf("%d\n", cntOfSort);
	}
	return 0;
}