#include <stdio.h>

#include <string.h>

int main() {
    int n;
    scanf("%d\n", &n);
    char names[n][101];
    char max[101];
    for (int i = 0; i < n; i++) {
        gets(names[i]);
    } //right
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            strcpy(max, names[i]);
            if (strlen(names[j]) > strlen(max)) {
                strcpy(max, names[j]);
            }
        }
    }
    printf("%s\n", max);
    return 0;
}
