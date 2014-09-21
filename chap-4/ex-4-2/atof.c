/* Exercise 4-2. Extend atofto handle scientific notation of the form 123.45e-6 where a floating-point number may
be followed by eor Eand an optionally signed exponent. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define STATE0 (1 << 0)
#define STATE1 (1 << 1)
#define STATE2 (1 << 2)
#define STATE3 (1 << 3)
#define STATE4 (1 << 4)
#define STATE5 (1 << 5)
#define STATE6 (1 << 6)
#define STATE7 (1 << 7)


double atof(char *, int *);

int main(void) {
	
	char *test_seq[] = {"", " 	", "  123.34  ", " 123", "123.", "13j", ".34", "-13.45 ", "-123.45e-1", 
" -123.45E+3", "  123.45-5  ", "12.random ", " 122.34e11  rnd", " .23e5\t	", ".23e-5", "random stuff.."};
	char *cstring;
	int len = sizeof(test_seq) / sizeof(test_seq[0]);
	double res;
	int status, i;
	for (i = 0; i < len; i++) {
		status = 0;		
		cstring = test_seq[i];
		res = atof(cstring, &status);	
		if (status == 0) 
			printf("test %d: %s\nresult: %g\n\n", i, cstring, res);	
		else
			printf("test %d: %s\nINVALID!\n\n", i, cstring);
	}
	
	return 0;
}


/* convert string to double, handles scientific notation, status is 0 on success, -1 on error, FSM style coding */
double atof(char *s, int *status) {

	char *s_st, *s_end;	
	int sign = 1;
	int expsign = 1;
	double val = 0.0;
	double pow = 1.0;
	double expval = 0.0;
	double ret;
	
	int state;
	for (s_st = s;*s_st != '\0' && isspace(*s_st); s_st++);
	for (s_end = s + strlen(s) - 1; s_end >= s_st && isspace(*s_end); s_end--); 

	/* corner case: empyt str */	
	if (s_st > s_end) {
		*status = -1;
		return 0;
	}


	state = STATE0;	
	*status = 0;
	while (s_st <= s_end && *status != -1) {
		
		switch (state) {
			case STATE0:
				if (*s_st == '+' || *s_st == '-') {
					sign = (*s_st == '-')? -1 : 1;
					state = STATE1;
				} else if (*s_st == '.') { 
					state = STATE3;
				} else if (isdigit(*s_st)) {
					sign = 1;
					val = val * 10 + (*s_st - '0');;;;
					state = STATE2;
				} else {
					/* invalid input */
					*status = -1;
				} break;

			case STATE1:
			case STATE2:
				if (*s_st == '.') state = STATE3;
				else if (isdigit(*s_st)) {
					val = val * 10 + *s_st - '0';	
					state = STATE2;
				} else {
					*status = -1;
				} break;
				
			case STATE3:
				if (isdigit(*s_st)) {
					val = val * 10 + (*s_st - '0');
					pow *= 10;
					state = STATE4;
				} else {
					*status = -1;
				} break;
			case STATE4:
				if (isdigit(*s_st)) {
					val = val * 10 + (*s_st - '0');
					pow *= 10;
				} else if (*s_st == 'e' || *s_st == 'E') {
					state =  STATE5;
				} else {
					*status = -1;
				} break;
			case STATE5:
				if (*s_st == '+' || *s_st == '-') {
					expsign = (*s_st == '-')? -1 : 1;
					state = STATE7;	
				} else if (isdigit(*s_st)) {
					expsign = 1;
					expval = expval * 10 + *s_st - '0';
					state = STATE6;
				} else {
					*status = -1;
				} break;
			case STATE6:
			case STATE7:
				if (isdigit(*s_st)) {
					expval = expval * 10 + *s_st - '0';	
					state = STATE6;
				} else {
					*status = -1;	
				} break;	
			default: *status = -1; break;
		}	
	s_st++;	
	}	
	if (*status == -1)	return 0;		
	if (state & (STATE2 | STATE4 | STATE6)) {
		ret = sign * val / pow;
		/* just reuse sign, and pow */
		for (sign = 0, pow = 1; sign < expval; sign++)	pow = pow * 10; 
		return (expsign == 1)? ret * pow : ret / pow;
	} else {
		*status = -1;
		return 0;
	} 	
		
}
