#include <stdio.h>
long int cal_Step (long int a[], int n) {
    return a[n] = a[n - 2] + a[n - 3];
}
int main() {
	int N; //��̨����
    scanf("%d", &N);
    long int step[50];//step[N]N��̨�׵ķ�����
    step[0] = 0;
    step[1] = 0;
    step[2] = 1;
    step[3] = 1;
    for (int i = 4; i <= N; i++) {
        step[i] = step[i - 2] + step[i - 3];
    }
    printf("%ld", step[N]);
    return 0;
}
