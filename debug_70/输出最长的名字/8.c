#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d\n", &n);
    char name[1001][102];
    int i, j;
    char largest[1001];
    for (i = 0; i < n; i++)
        for (j = 0; scanf("%c", &name[i][j]) != EOF && name[i][j] != '\n'; j++);

    for (strcpy(largest, name[0]), i = 1; i < n; i++)
        if (strlen(largest) < strlen(name[i]))
            strcpy(largest, name[i]);
    printf("%s\n", largest);

    return 0;
}
