#include <stdio.h>
#include <string.h>

int hash(char input[]) {
	char output[33];//要输出的字符串数组
	int bits[32];
	int arr[32] = { 0 };
	int i;
	int j;
	int m = strlen(input);
	for (i = 0; i < m; i++) {
		arr[(i + 1) % 32] += input[i];
	}
	for (j = 0; j <= 31; j++) {//(0<=j<=31)
		bits[j] = arr[31 - j] ^ (arr[j] << 1);
		printf("%c", bits[j] % 85 + 34);
	}
	return 0;
}
int main() {
	char input[500];
	scanf("%s", input);
	hash(input);
	return 0;
}
