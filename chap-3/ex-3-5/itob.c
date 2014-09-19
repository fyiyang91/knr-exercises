/* Exercise 3-5.Write the function itob(n,s,b)that converts the integer n into a base bcharacter representation in the string 
s. In particular, itob(n,s,16) formats sas a hexadecimal integer in s. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char charset[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int reverse(char *, int, int);
int itob(int, char *, int);


int main(void) {
	char buf[1024] = {0};

	itob(134, buf, 2);
	printf("134 to base-2: %s\n", buf);

	itob(123, buf, 8);
	printf("123 to base-8: %s\n", buf);

	itob(12, buf, 9);
	printf("12 to base-9: %s\n", buf);

	itob(253, buf, 16);	
	printf("253 to base-16:%s\n", buf);
	return 0;
}


/* integer to base-b string, n to base b char conversion, return 0 on success, -1 on error 
NOTE: b falls between [2, 16] */
int itob(int n, char *s, int b) {

	int sign, i;	
	if (b < 2 || b > 16)	return -1;	
	if (n < 0)	sign = -1;
		
	i = 0;
	while (n != 0) {
		s[i++] = charset[abs(n % b)];
		n /= b;
	}
	if (sign == -1)	s[i++] = '-';
	s[i] = '\0';
	reverse(s, 0, strlen(s) - 1);
	return 0;	
}


/* inplace string reverse, return 0 on success, 1 on error */
int reverse(char s[], int start, int end) {
        if (start > end) return -1; // invalid index
        int i,j; 
        for (i = start, j = end; i < j; i++, j--) {
		/* use xor to get rid of the temp variable for swapping */
                s[i] ^= s[j];
                s[j] ^= s[i];
                s[i] ^= s[j];   
        }       
        return 0;       
}

