#include <stdio.h>

int main() {
    int n = 10;
    int m;
    int numbers[10];
    int i;
    int max;
    int k;
    int j;
    int o;
    // 读入给定的数字
    for (i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    for (j = 0; j < n; j++) {
		m = j;
        for(k = j; k < n - 1; k++){
            if(numbers[m] < numbers[k+1]){
                m = k + 1;
            }
          //from j,find the max 
        }
        o = numbers[j];
        numbers[j] = numbers[m];
        numbers[m] = o;//max<->j
    }
    for (int q = 0; q < n; q++) {
        if (q == 9) {
            printf("%d", numbers[q]);
        } else {
            printf("%d ", numbers[q]);
        }
    }

    return 0;
}
