/* Exercise 3-3.Write a function expand(s1,s2)that expands shorthand notations like a-zin the string s1 into 
the equivalent complete list abc...xyzin s2. Allow for letters of either case and digits, and be prepared to
handle cases like a-b-cand a-z0-9and -a-z. Arrange that a leading or trailing -is taken literally. 

Note: My implementation only checks whether shorthand notation is in correct (logical) format, it doesn't
check against case that any other invalid string as test string */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUF_MAX_LEN 1024
#define STATE0 (1 << 0)
#define STATE1 (1 << 1)
#define STATE2 (1 << 2)

int expand(char *, char *);

int main(void) {
	
	char *test_seq[] = {"----0-1-3a-fA-B-Z---", "0-1-3a-b-c-d-zA-B-Z-", "0z-Z--", }; 
	char res_buf[BUF_MAX_LEN] = {0};
	int test_len = sizeof(test_seq) / sizeof(test_seq[0]);
	int status, i;
	char * cstr;	
	for (i = 0; i < test_len; i++) {
		
		memset((void*)res_buf, '\0', sizeof(res_buf));	
		cstr = test_seq[i];	
		status = expand(cstr, res_buf);
		if (0 == status) {
			printf("test #%d, raw string: \n%s\nexpanded string :\n%s\n\n", i, cstr, res_buf);	
		} else {
			printf("test #%d, raw string: \n%s\nraw string is INVALID!\n\n", i, cstr);
		}	
	}	
	return 0;
}




/* Shorthand notation expansion, expand string s to s2, return 0 on success, -1 on error, finite state machine
style coding*/
int expand(char *s, char *s2) {
	
	char *s_end;
	char state = STATE0;
	char checkpt, c;
	char first_in = 1;
	while (*s == '-') *s2++ = *s++;

	s_end = s;
	while (*s_end != '\0') s_end++;
	s_end--;

	while (*s_end == '-') s_end--;		
	
	while (s <= s_end) {
		switch (state) {
			case STATE0: 
				if (*s == '-') return -1;
				else {
					checkpt = *s;			
					*s2++ = checkpt;
					state = STATE1;
				} break;	
			case STATE1: 
				if (*s == '-') state = STATE2;
				else {
					if (first_in) {
						first_in = 0;
						checkpt = *s;
						*s2++ = checkpt;
					} else {
						for (c = checkpt + 1; c <= *s; c++) 
							*s2++ = c;
						checkpt = *s;		
					}
					state = STATE1;
				} break;
			case STATE2:
				if (*s == '-') return -1;
				else if (
					(isdigit(checkpt) && isdigit(*s) && *s > checkpt && *s <= '9') ||
					(isupper(checkpt) && isupper(*s) && *s > checkpt && *s <= 'Z') ||
					(islower(checkpt) && islower(*s) && *s > checkpt && *s <= 'z')
					) {
						for (c = checkpt + 1; c <= *s; c++) {
							*s2++ = c;	
						}
						checkpt = *s;
						state = STATE1;
					} 
				else return -1;
				break;
			default:  return -1; break;// error state
		}
		s++;	
	}
	while (*s_end != '\0') {
		*s2++ = *s_end++;
	}
	return 0;
}


