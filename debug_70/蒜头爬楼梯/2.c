#include <stdio.h>
int main() {
    int N; //总台阶数
    scanf("%d", &N);
    long int step[50]; //step[N]N级台阶的方法数
    int i;
    step[0] = 0;
    step[1] = 0;
    step[2] = 1;
    step[3] = 1;
    step[4] = 1;
    for (i = 4; i <= N; i++) {
        step[i] = step[i - 2] + step[i - 3];
    }
    printf("%ld", step[N]);
    return 0;
}
