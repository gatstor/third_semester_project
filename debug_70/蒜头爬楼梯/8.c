#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    int i = 0;
    for (int x = 0; x <= n / 2; x++) {
        for (int y = 0; y <= n / 3; y++) {
            if (x * 2 + y * 3 == n) {
				long double m = 1.0;
				long double b = 1.0;
               	for (int k = x + y; k > y; k--)
					m *= k;
				for (int k = x; k > 0; k--)
					b *= k;
				i = i + (int)(m / b);
            }
        }
    }
    printf("%d", i);
    return 0;
}
