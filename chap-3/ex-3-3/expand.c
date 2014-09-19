/* Exercise 3-3. Write a function expand(s1,s2)that expands shorthand notations like a-zin the string s1 into 
the equivalent complete list abc...xyzin s2. Allow for letters of either case and digits, and be prepared to
handle cases like a-b-cand a-z0-9and -a-z. Arrange that a leading or trailing -is taken literally. 

Note: My implementation treats empty string "" as invalid, and any characters than alphanumeric value or '-' 
are also treated as invalid. Besides it supports reverse or interleaved short hand notations. e.g. "--a--e-a--"
is expanded to "--abcdedcba--". */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUF_MAX_LEN 30
#define STATE0 (1 << 0)
#define STATE1 (1 << 1)
#define STATE2 (1 << 2)
#define STATE3 (1 << 3)
#define STATE4 (1 << 4)

int expand(char *, char *, int);

/* to illustrate the buffer overflow case, use global array, otherwise gcc issues stack smashing, and terminate
the program */
char res_buf[BUF_MAX_LEN] = {0};

int main(void) {
	
	char *test_seq[] = {"----0-1-3a-fA-B-Z---", "0-1-3a-b-c-d-zA-B-Z-", "0z-Z--", "---blabla89jk----",
	"-- afsd--", "------", "", "0--2--", "jT-Z-B--", "---------------------------bbb-----------"}; 
	// char res_buf[BUF_MAX_LEN] = {0};
	int test_len = sizeof(test_seq) / sizeof(test_seq[0]);
	int status, i;
	char * cstr;	
	for (i = 0; i < test_len; i++) {
		
		memset((void*)res_buf, '\0', sizeof(res_buf));	
		cstr = test_seq[i];	
		status = expand(cstr, res_buf, sizeof(res_buf));
		if (0 == status) {
			printf("test #%d, raw string: \n%s\nexpanded string :\n%s\n\n", i, cstr, res_buf);	
		} else {
			printf("test #%d, raw string: \n%s\nraw string is INVALID!\n\n", i, cstr);
		}	
	}	
	return 0;
}



/* Shorthand notation expansion, expand string s1 to s2, return 0 on success, -1 on error, finite state machine
style coding*/
int expand(char *s1, char *s2, int s2_buf_len) {
	
	char *s_st, *s_end;
	char check_c;
	int i;
	
	int state = STATE0;
	/* empty string or buffer overflow */
	if (!*s1 || strlen(s1) + 1 > s2_buf_len)  return -1;

	/* keep leading and trailing '-' as they are */
	for (s_st = s1; s_st != '\0' && *s_st == '-'; s_st++);
	for (s_end = s1 + strlen(s1) - 1; s_end >= s_st && *s_end == '-'; s_end--);
	
	/* fill the leading '-' */
	for (i = 0; i < s_st - s1; i++)  s2[i] = s1[i];
	
	while (s_st <= s_end) {
		switch (state) {
			case STATE0: 
				check_c = *s_st;
				if (isupper(*s_st) || islower(*s_st)) state = STATE1;
				else if (isdigit(*s_st))  state = STATE2;
				else return -1; break;	
			case STATE1:
				s2[i++] = check_c;	
				if (*s_st == '-')  state = STATE3; 
				else {
					check_c = *s_st;
					if (isdigit(*s_st)) state = STATE2;
					else if (!(isupper(*s_st) || islower(*s_st))) return -1;
				} 
				break;					
			case STATE2: 
				s2[i++] = check_c;
				if (*s_st == '-')  state = STATE4;
				else {
					check_c = *s_st;
					if (islower(*s_st) || isupper(*s_st)) state = STATE1;
				else if (!isdigit(*s_st)) return -1;
				} break;	
			case STATE3:
				if (isupper(*s_st) || islower(*s_st)) {
					char temp_c;
					if ((isupper(*s_st) && !isupper(check_c)) ||
						(islower(*s_st) && !islower(check_c)))  return -1;
					if (*s_st >= check_c) {
						for (temp_c = check_c + 1; temp_c < *s_st; temp_c++) s2[i++] = temp_c;
					} else {
						for (temp_c = check_c - 1; temp_c > *s_st; temp_c--) s2[i++] = temp_c;
					}	
					check_c = *s_st;
					state = STATE1;
				} else return -1;
				break;
			case STATE4:
				if (isdigit(*s_st)) {
					char temp_c;
					if (isdigit(*s_st) && !isdigit(check_c))  return -1;
					if (*s_st >= check_c) {
				    	  for (temp_c = check_c + 1; temp_c < *s_st; temp_c++) s2[i++] = temp_c;
					} else {
					  for (temp_c = check_c - 1; temp_c > *s_st; temp_c--) s2[i++] = temp_c;
					}	
					check_c = *s_st;
					state = STATE2;
				} else return -1;
				break; 
			default: return -1; break;
		}				
		s_st++;
	}
	if (state & (STATE1 | STATE2)) s2[i++] = check_c; 	
        for (s_end++; *s_end != '\0'; s_end++)  s2[i++] = *s_end;
	s2[i] = '\0';
	return 0;
}

