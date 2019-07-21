#include <stdio.h>
#include <math.h>
void swap(int*a,int*b){
    int temp;
    temp=*a;
	*a=*b;
    *b=temp;
}

int main() {
    int n = 10;
    int m;
    int numbers[100];
 	int i,j;
	for (i = 0; i < n; i++) {
		scanf("%d", &numbers[i]);
	}
	for (i = 0; i < n; i++) {
		for (j = n - 1; j > i; j--) {
			if (numbers[j - 1] < numbers[j]) {
				swap(&numbers[j - 1], &numbers[j]);
			}
		}
	}

    for(m=0;m<10;m++){
        printf("%d",numbers[m]);
        if(m!=9){
            printf(" ");
        }
    }
    return 0;
}
