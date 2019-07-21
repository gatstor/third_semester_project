#include <stdio.h>
#include <string.h>
int main() {
	char str[500], result[33];
    int arr[32] = { 0 }, bits[32];
	int i;
	memset(arr, 0, sizeof(arr));
	memset(result, '\0', sizeof(result));
	scanf("%s", str);
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] == '\n') {
			break;
		}
		arr[(i + 1) % 32] += str[i];
	}
	for (i = 0; i < 32; i++)
	{
		bits[i] = (arr[31 - i]) ^ (arr[i] << 1);
		result[i] = bits[i] % 85 + 34;
	}
	result[i] = '\0';
	printf("%s", result);
	return 0;
}
