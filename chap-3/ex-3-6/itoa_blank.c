/* Exercise 3-6.Write a version of itoathat accepts three arguments instead of two. The third argument is a minimum field
width; the converted number must be padded with blanks on the left if necessary to make it wide enough. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverse(char *, int, int);
void itoa_blank(int, char *, int);


int main(void) {
	
	char buf[1024] = {0};

	itoa_blank(333, buf, 5);
	printf("%d with min width of %d is:\n%s\n\n", 333, 5, buf);

	itoa_blank(1029, buf, 3);
	printf("%d with min width of %d is \n%s\n\n", 1029, 3, buf);

	itoa_blank(1 << 31, buf, 20);
	printf("%d with min width of %d is \n%s\n\n", 1 << 31, 20, buf);

	return 0;
}


/* integer to string, convert n to string in s, if s is shorter len min_width, space is padded at the left */
void itoa_blank(int n, char s[], int min_width) {
	
	int sign, i;
	if (n < 0) sign = -1;
	i = 0;
	while (n != 0) {
		s[i++] = abs(n % 10) + '0';
		n /= 10;
	} 
	if (sign == -1)	s[i++] = '-';
	while(min_width - i > 0)	s[i++] = ' ';
	s[i] = '\0';	
	reverse(s, 0, strlen(s) - 1);
	
}



/* inplace string reverse, return 0 on sucess, -1 on error */
int reverse(char s[], int start, int end) {
        if (start > end) return -1; // invalid index
        int i,j;
        for (i = start, j = end; i < j; i++, j--) {
                s[i] ^= s[j];
                s[j] ^= s[i];
                s[i] ^= s[j];
        }
        return 0;
}




