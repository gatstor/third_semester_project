#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d\n", &n);
    char names[n][101];
    char max[101];
    char p[101] = "\0";
    for (int i = 0; i < n; i++) {
        gets(names[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strlen(names[j]) > strlen(p))
                strcpy(p, names[j]);
        }
    }
    printf("%s\n", p);
    return 0;
}
