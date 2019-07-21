#include <stdio.h>

int main() {
    int a;
    int b;
    int c;
    scanf("%d", &a);
    for (b = 2; b <= a; b++) {
        for (c = 2; c <= b; c++) {
            if (b % c == 0 && b != c) {
                break;
            }
            else if (c == b - 1 || b == 2) {
                printf("%d\n", b);
            }
        }
    }
    return 0;
}
