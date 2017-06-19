#include <stdio.h>
#include <string.h>
#include <list>
#include <math.h>

int mem[200][100]; // �ʱ⿡ ������ �Է� ��, �ߺ��ؼ� ������ ���� �Ǵܿ��� �迭
std::list<int> lst[200]; // int�� list ������ �迭

int main() {
	int testCase;
	int cntOfCard, cntOfMem, data;
	int i, j, k;
	int total = 0; // ��Ƶ��� ��� ī���� ����
	int index = 0; // ���� �ε���
	int order = 0; // ����
	int temp = 0;
	int input = 0;
	std::list<int>::iterator it;
	char line[1024];
	char ch;
	int digitCount = 0;

	scanf("%d", &testCase);
	for (testCase; testCase > 0; testCase--) {
		scanf("%d %d", &cntOfCard, &cntOfMem);
		memset(mem, 0, sizeof(int) * 200 * 100);
		memset(line, 0, sizeof(char) * 1024);

		total = 0;
		index = 0;
		order = 0;
		temp = 0;
		input = 0;

		fgets(line, sizeof(char) * 1024, stdin);
		// �Է� ����
		for (i = 0; i < cntOfMem; i++) {
			fgets(line, sizeof(char) * 1024, stdin);
			j = 0;
			while (line[j] != '\n') {
				ch = line[j];
				if (ch >= '0' && ch <= '9') {
					digitCount = 0;
					input = 0;
					for (k = j; line[k] != ' ' && line[k] != '\n'; k++)
						digitCount++;
					for (k = j + digitCount - 1; k >= j; k--) {
						temp = (int)(line[k] - '0');
						input += pow(10, j + digitCount - 1 - k) * temp;
					}
					lst[i].push_back(input);
					mem[i][input - 1]++;
					total++;
					if (mem[i][input - 1] == 2) {
						mem[i][input - 1] = 0;
						total -= 2;
						lst[i].remove(input);
						lst[i].remove(input);
					}
					j += digitCount;
				}
				else
					j++;

			}
		}

		i = 0;
		while (total > 1) {
			if (i >= cntOfMem)
				i %= cntOfMem;

			if (lst[i].empty()) {
				i++; // ī�带 ��� �����Ͽ����Ƿ� ���ӿ��� ������
				continue;
			}

			j = (i + 1) % cntOfMem;

			while (lst[j].empty()) {
				j++;
				j %= cntOfMem;
			}

			order = (i + 1) % (cntOfMem + 1);

			if (order > lst[j].size()) {
				data = lst[j].back();
				lst[j].pop_back();
			}
			else {
				it = lst[j].begin();
				std::advance(it, order - 1);
				data = *it;
				lst[j].erase(it);
			}

			bool bFind = false; // �ϳ��� ������κ��� ī�带 ���� �ٸ� ������� ī�带 ���� ��, �� �� ������ �����Ͱ� ������ true, �׷��� ������ false
			bool bEnd = false; // �� �ڿ� ���� ����.
			for (it = lst[i].begin(); it != lst[i].end(); it++) {
				if (data == *it) {
					bFind = true;
					lst[i].erase(it);
					total -= 2;
					break;
				}
			}
			// �ߺ��� �����Ͱ� ���� ���
			if (!bFind) {
				it = lst[i].begin();
				bEnd = false;
				while (*it <= data) {
					it++;
					if (it == lst[i].end()) {
						bEnd = true;
						break;
					}
				}
				if (bEnd)
					lst[i].push_back(data);
				else
					lst[i].insert(it, data);
			}
			i = j;
		}
		for (i = 0; i < cntOfMem; i++) {
			if (!lst[i].empty()) {
				index = i + 1;
				lst[i].clear();
				break;
			}
		}
		printf("%d\n", index); // ���� �ε��� ���
	}
	return 0;
}