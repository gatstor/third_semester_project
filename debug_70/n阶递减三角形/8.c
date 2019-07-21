#include <stdio.h>

int main() {
    int n;
    int j;
    int i;
    int n2;
    scanf("%d", &n);
    n2 = n;
    for (i = 1; i <= n; i++)
    {
        n2 = n - i + 1;
        for (j = 1; j <= n; j++)
        {
            printf("%d", n2);
            if (n2 > 1)
            {
                printf(" ");
            }
            if (n2 == 1)
            {
                break;
            }
            n2--;
        }
        printf("\n");
    }
    return 0;
}
