#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BOARD_MAX 5001
#define CARD_MAX 2501

int board[BOARD_MAX][BOARD_MAX];
int cardA[CARD_MAX];
int cardB[CARD_MAX];
unsigned short hashArrayX[CARD_MAX*CARD_MAX];
unsigned short hashArrayY[CARD_MAX*CARD_MAX];

int main() {
	int tc;
	scanf("%d", &tc);
	for (int v = 0; v < tc; v++) {
		int M, N;
		int aIndex, bIndex, hpOfA, hpOfB, cntOfCard;
		int xOfA, xOfB, yOfA, yOfB;

		scanf("%d %d", &N, &M);
		int i, j, temp; // loop iterator, ÀÓ½Ãº¯¼ö
		memset(board, 0, sizeof(int)*BOARD_MAX*BOARD_MAX);
		memset(hashArrayX, 0, sizeof(unsigned short)*CARD_MAX*CARD_MAX);
		memset(hashArrayY, 0, sizeof(unsigned short)*CARD_MAX*CARD_MAX);
		for (i = 0; i < N; i++) {
			for (j = 0; j < M; j++) {
				scanf("%d", &board[i][j]);
				hashArrayX[board[i][j]] = j;
				hashArrayY[board[i][j]] = i;
			}
		}

		int game = 0;
		scanf("%d", &game);
		for (i = 0; i < game; i++) {
			aIndex = 0;
			bIndex = 0;
			scanf("%d", &cntOfCard);
			memset(cardA, 0, sizeof(unsigned int)*CARD_MAX);
			memset(cardB, 0, sizeof(unsigned int)*CARD_MAX);
			for (j = 0; j < cntOfCard; j++) 
				scanf("%d", &cardA[j]);			
			for (j = 0; j < cntOfCard; j++) 
				scanf("%d", &cardB[j]);

			int hp = 0;
			int posx = 0;
			int posy = 0;
			scanf("%d", &hp);
			scanf("%d %d", &posy, &posx);

			hpOfA = hp;
			hpOfB = hp;

			xOfA = posx;
			yOfA = posy;
			xOfB = posx;
			yOfB = posy;

			int ord = 0;
			int find = 0;
			int c1;
			int c2;

			int col = 0;
			int row = 0;
			int con = 0;
			int tmp3 = 0, tmp4 = 0;
			//more fast find routine
			while (con == 0) {
				int afterX, afterY;
				if (ord == 0) { // A start, B hp --;
					if (aIndex >= cntOfCard)
						aIndex %= cntOfCard;
					c1 = cardA[aIndex % cntOfCard];
					c2 = cardA[(aIndex+1) % cntOfCard];
					aIndex += 2;

					find = c1*c2;					
					afterX = hashArrayX[find];
					afterY = hashArrayY[find];

					tmp3 = xOfB - afterX;
					col = tmp3 >= 0 ? tmp3 : -tmp3;
					tmp4 = yOfB - afterY;
					row = tmp4 >= 0 ? tmp4 : -tmp4;
					hpOfB -= (col + row);

					xOfB = afterX;
					yOfB = afterY;
					if (hpOfB <= 0) {
						con = 2; //A°¡ÀÌ±è
						break;
					}
					ord = 1;
				}
				else if (ord == 1) {
					if (bIndex >= cntOfCard)
						bIndex %= cntOfCard;
					c1 = cardB[bIndex % cntOfCard];
					c2 = cardB[(bIndex + 1) % cntOfCard];
					bIndex += 2;

					find = c1*c2;
					afterX = hashArrayX[find];
					afterY = hashArrayY[find];

					tmp3 = xOfA - afterX;
					col = tmp3 >= 0 ? tmp3 : -tmp3;
					tmp4 = yOfA - afterY;
					row = tmp4 >= 0 ? tmp4 : -tmp4;
					hpOfA -= (col + row);

					xOfA = afterX;
					yOfA = afterY;
					if (hpOfA <= 0) {
						con = 1; //B°¡ÀÌ±è
						break;
					}
					ord = 0;
				}
			}
			if (con == 1) {
				printf("B\n");
			}
			else if (con == 2) {
				printf("A\n");
			}
		}
	}
	return 0;
}