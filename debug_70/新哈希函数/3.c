#include <stdio.h>
#include <string.h>
int main() {
	int arr[32];
	memset(arr, 0, sizeof(arr));
	char character;
	int i = 1;
	while (scanf("%c", &character) != EOF) {
		if (character == '\n') {
			break;
		}
		int c = (int)character;
		arr[i % 32] += c;
		i++;

	}
	int bits[32];
	int j;
	for (j = 0; j < 32; j++) {
		int d = arr[31 - j] ^ (arr[j] << 1);
		bits[j] = d;
	}
	for (j = 0; j < 32; j++) {
		int d = bits[j] % 85 + 34;
		char t = (char)d;
		printf("%c", t);
	}

	return 0;
}
