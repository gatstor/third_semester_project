#include <stdio.h>

int main() {
	int matrix[100][100];
	int m;
	int n;
	int row = 0;
	int column = 0;
	int num = 0;
	scanf("%d %d", &m, &n);
	int mOrigin = m ,nOrigin = n;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	while (row < m && column < n){
		/* Print the first row from the remaining rows */
		for (int i = column; i < n; i++){
			printf("%d", matrix[row][i]);
			num++;
			if (num != mOrigin * nOrigin) {
				printf(" ");
			}
		}
		row++;
		/* Print the last column from the remaining columns */
		for (int i = row; i < m; i++){
			printf("%d", matrix[i][n - 1]);
			num++;
			if (num != mOrigin * nOrigin) {
				printf(" ");
			}
		}
		n--;
		/* Print the last row from the remaining rows */
		if (row < m){
			for (int i = n - 1; i >= column; i--){
				printf("%d", matrix[m - 1][i]);
				num++;
				if (num != mOrigin * nOrigin) {
					printf(" ");
				}
			}
			m--;
		}
		/* Print the first column from the remaining columns */
		if (column < n){
			for (int i = m - 1; i >= row; i--){
				printf("%d", matrix[i][column]);
				num++;
				if (num != mOrigin * nOrigin) {
					printf(" ");
				}
			}
			column++;
		}
	}

	return 0;
}
