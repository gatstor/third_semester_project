#include <stdio.h>
int main() {
    int n, i;
    int sum = 0;
    long int arr[51];
    scanf("%d", &n);
    arr[0] = 1;//2
    arr[1] = 1;//3
    arr[2] = 1;//4
    if (n < 3)
        printf ("1");
    else { 
        for (i = 3; i <= n; i++) {  
    	    arr[i] = arr[i - 2] + arr[i - 3];
    	    sum += 1;
    	}
    printf("%ld", arr[sum]);
    }
    return 0;
}
