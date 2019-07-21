#include <stdio.h>

void add(char);
void delete(char);
int rwx = 0;

int main() {
    //initiation
    char temp;
    scanf("%c", &temp);
    if (temp == 'x') rwx ^= (1 << 0);//give 1
    else if (temp == 'w') {
        rwx ^= (1 << 1);//give 2
        scanf("%c", &temp); 
        if (temp == 'x') rwx ^= (1 << 0);//add 1
    }
    else if (temp == 'r') {
        rwx ^= (1 << 2);//give 4
        scanf("%c", &temp);
        if (temp == 'w') {
			 rwx ^= (1 << 1);//add 2
			 scanf("%c",&temp);
 	         if(temp == 'x') rwx ^= (1 << 0);
		}
        else if (temp == 'x') rwx ^= (1 << 0);//add 1
    }
    //modification
	while (scanf("%c", &temp) != EOF){
		if(temp =='\n')
			continue;
        if (temp == '+') {
			scanf("%c",&temp);
            add(temp);
        }
        else if (temp =='-') {
			scanf("%c",&temp);
            delete(temp);
        }
	}
    //output
    printf("%d", rwx);
    return 0;
}

void add(char input) {
    if (input == 'r' && rwx / 4 != 1) rwx ^= (1 << 2);
    else if (input == 'w' && (rwx / 2 % 2 != 1)) rwx ^= (1 << 1);
    else if (rwx % 4 != 1) rwx ^= (1 << 0);
}

void delete(char input) {
    if (input == 'r' && rwx / 4 == 1) rwx ^= (1 << 2);
    else if (input == 'w' && (rwx / 2 % 2 == 1)) rwx ^= (1 << 1);
    else if (input =='x') rwx ^= (1 << 0);
}
