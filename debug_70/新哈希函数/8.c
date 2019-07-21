#include <stdio.h>
#include <string.h>

void hash(char[]);

int main()
{
	char string[500];
	scanf("%s", string);
	hash(string);
	return 0;
}

void hash(char string[])
{
	int arr[32], bits[32];
	char result[33];
	int i, j;
	unsigned long len;
	for (i = 0; i < 32; i++)
		arr[i] = 0;
	len = strlen(string);
	for (i = 1; i <= len; i++)
		arr[i % 32] += (int)string[i - 1];
	for (j = 0; j < 32; j++) {
		bits[j] = arr[31 - j] ^ (arr[j] << 1);
		result[j] = (char)(bits[j] % 85 + 34);
	}
	result[j] = '\0';
	for (j = 0; j < 32; j++){
		printf("%c", result[j]);
    }
   
    
}
