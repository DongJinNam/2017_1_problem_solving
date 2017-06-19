#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>

#define MAX_COUNT 2501
int arr[MAX_COUNT];

int main() {
	int tc, i, j, k; // loop iterator
	int v_count, l_count; // ��� ����, ���� ����
	int data, temp, index; // �ڷᱸ���� ���� ���� ������, �ӽð�, ��ġ
	int start, target; //���� ����, ��ǥ����	
	bool bFind = false;

	scanf("%d", &tc);
	for (i = tc; i > 0; i--) {
		bFind = false;
		scanf("%d %d", &v_count, &l_count);

		std::vector<int> lineVector[2*MAX_COUNT];

		for (j = 0; j < l_count; j++) {
			scanf("%d ", &temp);
			lineVector[2 * (j + 1)].push_back(temp);
		}

		scanf("%d %d", &start, &target); // ���� ���ΰ�, ��ǥ ����

		// array�� ��ġ�� ��� (�������� �������� Ž���� ����)
		index = target;
		for (j = 2*(l_count+1); j > 0; j--) {
			if (!lineVector[j].empty()) {
				data = lineVector[j].at(0);
				if (index == data || index == data + 1)
					index = index > data ? data : data + 1;
			}
			arr[j] = index;
		}

		// �������� �������� ��ٸ��� ž�ϴ�
		index = start;
		for (j = 2; j < l_count << 1; j++) {
			if (j % 2 == 1) { // Ȧ����, ���� ���� �ϳ��� �� �߰����� ���� �����Ѵ�.
				if (index + 1 == arr[j] || index - 1 == arr[j]) {
					bFind = true;
					break;
				}
			}
			else {
				// ��ġ ���� �� ��ġ ����
				data = lineVector[j].at(0);
				if (index == data || index == data + 1)
					index = index > data ? data : data + 1;
			}
		}
		printf("%d\n", bFind == true ? 1 : 0);
	}
	return 0;
}