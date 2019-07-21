#include <stdio.h>
#include <string.h>

int main() {
	int arr[32];
	int bits[32];
	char result[33];
	char input;
	int j = 0;
	for (int i = 0; i < 32; i++) {
		arr[i] = 0;
	}
	while (scanf("%c", &input) != EOF) {
        if(input=='\n'){
            break;
        }
		arr[(j + 1) % 32] += (int)(input);
		j++;
	}
    int i;
	for (i = 0; i < 32; i++) {
		bits[i] = (arr[31 - i]) ^ (arr[i] << 1);
		int b = (bits[i] % 85) + 34;
		result[i] = (char)b;
	}
    result[i]='\0';
	for (int i = 0; i < 32; i++) {
		printf("%c", result[i]);
	}
	return 0;
}
