#include <stdio.h>
#include <string.h>

int main() {
    int n;
    int i, j;
    scanf("%d\n", &n);
    char string[n][120];
    for (i = 0; i < n; i++) {
        for (j = 0; j < 120; j++) {
            scanf("%c", &string[i][j]);
            if (string[i][j] == '\n') {
                string[i][j] = '\0';
                break;
            }
        }
    }
    char str[120];
    strcpy(str, string[0]);
    for (i = 0; i < n; i++) {
        if (strlen(string[i]) > strlen(str))
            strcpy(str, string[i]);
    }
    printf("%s", str);
    return 0;
}
