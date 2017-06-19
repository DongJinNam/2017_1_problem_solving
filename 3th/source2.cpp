#include <stdio.h>
#include <iostream>

int main() {
	int testCase,i,j,k,cntOfArray,cntOfSort;
	int arr[300];
	scanf("%d", &testCase);
	for (i = 0; i < testCase; i++) {
		scanf("%d", &cntOfArray);
		for (j = cntOfArray; j > 0; j--) {
			scanf("%d", &arr[j-1]);
		}
		// sorting
		cntOfSort = 0;
		for (j = 1; j < cntOfArray; j++) {
			for (k = 0; k < j; k++) {
				if (arr[j] < arr[k]) {
					std::swap(arr[j], arr[k]);
					cntOfSort++;
				}
			}
		}
		printf("%d\n", cntOfSort);
	}
	return 0;
}