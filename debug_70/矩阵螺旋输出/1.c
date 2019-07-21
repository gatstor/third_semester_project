#include <stdio.h>
#include<math.h>

int main() {
    int matrix[100][100];
    int m;
    int n;
    int i, j;
    int x;
    scanf("%d%d", &m, &n);
    for (i = 0; i < m; i++) {
    	for (j = 0; j < n; j++) {
    		scanf("%d", &matrix[i][j]);	
		}
	}
	int sub = 0 ;//sub的作用是记录输出的重数
    int count = 0 ;
	while (m - 2 * sub  >= 1 && n - 2 * sub >= 1) {
		for (x = sub; x <= n - 1 - sub; x++) {
			printf("%d", matrix[sub][x]);
			count++;
			if (count < m*n)
				printf(" ");
			else
				return 0;
		}
		for (x = sub + 1; x <= m - 1 - sub ; x++) {
			printf("%d", matrix[x][n - 1 - sub]);
		    count++;
            if (count < m*n)
                printf(" ");
			else 
				return 0;
		}
		for (x = sub + 1; x <= n - 1 - sub; x++) {
			printf("%d", matrix[m - 1 - sub][n - 1 - x]);
			count++;
			if (count < m*n)
				printf(" ");
			else 
				return 0;

		}
		for (x = sub + 1; x < m - 1 - sub; x++) {
			printf("%d", matrix[m - 1 - x][sub]);
			count++;
            if (count < m*n)
                printf(" ");
			else 
				return 0;

		}
		sub++;
	}	

    return 0;
}
