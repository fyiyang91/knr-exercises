/* Exercise 3-2.Write a function escape(s,t)that converts characters like newline and tab into visible escape sequences
like \nand \t as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting
escape sequences into the real characters. */
#include <stdio.h>

void escape(char *, char *);
void unescape(char *, char *);


int main(void) {
	char raw_buf[1024] = "Mysterious string in the next line, \ndid you find it?\t\t\n\"Encore\"";
	char escape_buf[1024]; 
	
	escape (escape_buf, raw_buf);

	printf("raw text is:\n%s\n", raw_buf);
	printf("escape text is:\n%s\n", escape_buf); 
	
	printf("\n\n");

	unescape (escape_buf, raw_buf);	
	printf("reverse operation, the unescaped text is:\n%s\n", raw_buf);
	return 0;
}

/* copy char from t to s, unconvert escape chars */
void unescape(char *t, char *s) {
	
	while (*t != '\0') {
		switch (*t) {
			case '\\':
				t++;
				switch (*t) {
					case 'a': *s++ = '\a'; break;
					case 'b': *s++ = '\b'; break;
					case 'f': *s++ = '\f'; break; 
					case 'n': *s++ = '\n'; break;
					case 'r': *s++ = '\r'; break;
					case 't': *s++ = '\t'; break;
					case 'v': *s++ = '\v'; break;
					case '\\': *s++ = '\\'; break;
				    	case '\'': *s++ = '\''; break;
					case '\"': *s++ = '\"'; break;
					case '?': *s++ = '\?'; break;		
					default: break;
				} 
				break; 
					
			default:   *s++ = *t;break;
		}
		t++;	
	}
	*s = '\0';
}


/* copy char from t to s converting escape chars */
void escape(char *t, char *s) {

	while (*s != '\0') {
		switch (*s) {
			case '\a': *t++ = '\\'; *t++ = 'a'; break;
			case '\b': *t++ = '\\'; *t++ = 'b'; break;
			case '\f': *t++ = '\\'; *t++ = 'f'; break;
			case '\n': *t++ = '\\'; *t++ = 'n'; break;
			case '\r': *t++ = '\\'; *t++ = 'r'; break;
			case '\t': *t++ = '\\'; *t++ = 't'; break;
			case '\v': *t++ = '\\'; *t++ = 'v'; break;
			case '\\': *t++ = '\\'; *t++ = '\\';break;
			case '\'': *t++ = '\\'; *t++ = '\\';break;
			case '\"': *t++ = '\\'; *t++ = '\"';break;
			case '\?': *t++ = '\\'; *t++ = '\?';break;
			default: *t++ = *s; break;
		}		
		s++;
	}
	*t++ = '\\';
	*t++ = '0';
	*t = '\0';
}

