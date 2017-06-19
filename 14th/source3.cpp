#include <stdio.h>
#include <string.h>

#define DIGIT 10

// �� : src, �� : dst (src ���ڷκ��� dst ���ڷ� �ٲٴµ��� �ʿ��� segment ����)
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

int digitArr[30]; // �Է� ���ڿ�
int resultArr[30]; // ��� ���ڿ�

// ���� ū ���ڸ� ã�� ���� ����Լ�
int processing(int temp, int index) {
	int i, rtn = -1;
	bool bFind = false;

	if (temp == 0) { // ó���� ���׸�Ʈ ������ 0�̹Ƿ�, �� ��� ���� ū ���ڸ� ã�Ҵٴ� �ǹ�
		return digitArr[index];
	}

	if (index == 0) { // ������ index
		for (i = DIGIT - 1; i >= 0; i--) {
			if (temp >= board[digitArr[index]][i]) {
				temp -= board[digitArr[index]][i];
				if (temp == 0) {
					bFind = true;
					break;
				}
				else
					temp += board[digitArr[index]][i]; // ���� �߻� ���, temp �� ���� ����				
			}
		}
	}
	else {
		for (i = DIGIT - 1; i >= 0; i--) {
			if (temp >= board[digitArr[index]][i]) {				
				temp -= board[digitArr[index]][i];				
				rtn = processing(temp, index - 1);
				if (rtn != -1) {
					bFind = true; // ū ���ڸ� ã�Ҵٴ� �ǹ�
					resultArr[index - 1] = rtn; // ���������κ��� (index-1) ��ġ�� ���� processing �Լ��� return ������ ����
					break;
				}
				else
					temp += board[digitArr[index]][i]; // ���� �߻� ���, temp �� ���� ����
			}
		}
	}	
	if (!bFind) // �����ִ� ���׸�Ʈ�� �߻��߰ų�, ���׸�Ʈ�� �ʰ��ؼ� ����� �� -1�� ���������ν� �������� calling function���� �˷��ش�.
		return -1;
	else
		return i;
}

int main() {
	int tc;
	int i, j, k;
	int cntSegment,cntToChange; // ���� ���׸�Ʈ ����,
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