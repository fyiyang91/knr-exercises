/* Exercise 3-4.In a two's complement number representation, our version of itoa does not handle the largest 
negative number, that is, the value of nequal to -(2^(wordsize-1)). Explain why not. Modify it to print that 
value correctly, regardless of the machine on which it runs. */

/* Solution: In original code, the negative number is converted to its complement, e.g. -128 becomes 0. However
if WORDSIZE is 8, -128 is 0b1000_0000. In two's complement system, flip the sign bit, it becomes 0 (0b0000_0000), 
The remedy is to use the negative number for computation, as marked in te code below*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int reverse(char*, int, int);
void itoa(int, char*);	


static void test_reverse(void) {
	char buf[1024] = "Is it there?";
	printf("before reverse: %s\n", buf);
	reverse(buf, 0, strlen(buf) - 1);
	printf("after reverse: %s\n", buf);
}


static void test_itoa(void) {
	char buf[1024] = {0};
	itoa(127, buf);
	printf("raw int %d is converted to:\n%s\n", 127, buf);
	itoa(-128, buf);
	printf("\nraw int %d is converted to:\n%s\n", -128, buf);
	itoa(1 << 31, buf); /* int is 32 bit in size, hence the test */
	printf("\nraw int %d is converted to:\n%s\n", 1 << 31, buf);
}

int main(void) {
	printf("reverse() test:\n");
	test_reverse();
	printf("\nitoa() test:\n");
	test_itoa();	
	return 0;
}



/* integer to string, convert n to string in s */
void itoa(int n, char s[]) {
	int i, sign;
	if (n < 0) sign = -1;
	i = 0;	
	while (n != 0) {
		s[i++] = abs((n % 10)) + '0'; /* single line change here */
		n /= 10;
	}	
	if (sign < 0) {
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s, 0, strlen(s) - 1);
}

/* in place reverse, from start to end 0 on success, 1 on error */
int reverse(char s[], int start, int end) {
	if (start > end) return -1; // invalid index
	int i,j; 
	for (i = start, j = end; i < j; i++, j--) {
		/* use xor operation to get rid of the temp variable for swapping */
		s[i] ^= s[j];
		s[j] ^= s[i];
		s[i] ^= s[j];	
	}	
	return 0;	
}
