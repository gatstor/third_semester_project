#include <stdio.h>

int main() {
	int matrix[100][100];
	int mOrigin;
	int nOrigin;
	int nIndex;
	int mIndex;
	int matrixpass[110][110];
	int orientation = 0;
	int i;
	int j;
	int times;
	int p = 0;
	//输入参数
	scanf("%d %d", &mOrigin, &nOrigin);
	for (i = 0; i < mOrigin; i++) {
		for (j = 0; j < nOrigin; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	//计数清零
	int m;
	int n;
	m = mOrigin;
	n = nOrigin;
	times = 0;
	mIndex = 0;
	nIndex = 0;
	for (i = 0; i < 110; i++) {
		for (j = 0; j < 110; j++) {
			matrixpass[i][j] = 0;
		}
	}
	if(times <= mOrigin * nOrigin) {
		for (i = 0; i < 60; i++) {
			if (orientation % 4 == 0) {  //right
				while (matrixpass[mIndex][nIndex] == 0 && nIndex <= n - 1) {
					printf("%d", matrix[mIndex][nIndex]);
					matrixpass[mIndex][nIndex] = 1;
					nIndex++;
					times++;
					if (times != mOrigin * nOrigin) {
						printf(" ");
					}
				}
				orientation++;
				mIndex++;
				nIndex--;
			}
			if (orientation % 4 == 1) {  //down
				while (matrixpass[mIndex][nIndex] == 0 && mIndex <= m - 1) {
					printf("%d", matrix[mIndex][nIndex]);
					matrixpass[mIndex][nIndex] = 1;
					mIndex++;
					times++;
					if (times != mOrigin * nOrigin) {
						printf(" ");
					}
				}
				orientation++;
				mIndex--;
				nIndex--;
			}
			if (orientation % 4 == 2) {  //left
				while (matrixpass[mIndex][nIndex] == 0 && nIndex >= p) {
					printf("%d", matrix[mIndex][nIndex]);
					matrixpass[mIndex][nIndex] = 1;
					nIndex--;
					times++;
					if (times != mOrigin * nOrigin) {
						printf(" ");
					}
				}
				orientation++;
				mIndex--;
				nIndex++;
			}
			if (orientation % 4 == 3) {  //up
				while (matrixpass[mIndex][nIndex] == 0 && mIndex >= p + 1) {
					printf("%d", matrix[mIndex][nIndex]);
					matrixpass[mIndex][nIndex] = 1;
					mIndex--;
					times++;
					if (times != mOrigin * nOrigin) {
						printf(" ");
					}
				}
				orientation++;
				mIndex++;
				nIndex++;
			}
			m--;
			n--;
			p++;
		}
	}
	return 0;
}
