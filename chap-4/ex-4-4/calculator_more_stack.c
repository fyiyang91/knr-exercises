/* Exercise 4-4. Add the commands to print the top elements of the stack without popping, to duplicate it, 
and to swap the top two elements. Add a command to clear the stack. */

/* Extended commands:
print top of stack: p(P)
swap top two elems: s(S)
clear stack: c(C)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0' // signals a number is found

int getop2(char []); // modified getop() function
void push(double);
double pop(void);
void clearall(void);
void printtop(void);
void swaptop2(void);

/* reverse Polish calculator */
int main(void) {

	int type;
	double op2;
	char s[MAXOP];
	
	while ((type = getop2(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else 
					printf("error: zero divisor\n");	
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push(fmod(pop(),op2));	
				else
					printf("error: modulo by zero\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			
			case 'p':
			case 'P': printtop(); break;	
			case 's':
			case 'S': swaptop2(); break;
			case 'c':
			case 'C': clearall(); break;
			default:
				printf("error: unknown command %s\n", s);
		}
	}
	return 0;
}	


#define MAXVAL 100
int sp = 0; // next free stack index
double val[MAXVAL];


/* push: push f onto value stack */
void push(double f) {
	if (sp < MAXVAL) 
		val[sp++] = f;
	else  printf("error: stack full, can't push %g\n", f);
}


/* pop: pop and return top value from stack */
double pop(void) {
	if (sp > 0) return val[--sp];
	else  printf("error: stack empty, can't pop\n");
	return 0.0;
}


/* printtop: print without pop top value from stack */ 
void printtop(void) {
	if (sp > 0) printf("top elem: %g\t", val[sp - 1]); 
	else printf("error: stack empty\n"); 
}


/* clearall: clear all stack contents */
void clearall(void) {
	sp = 0;
}

/* swaptop2: swap top 2 elements */
void swaptop2(void) {
	extern double val[];
	if (sp > 1) {
		double temp = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = temp;
	}
	else printf ("error: less than 2 elems on stack\n");
}
#include <ctype.h>

int getch(void);
void ungetch(int);


/* support negation number, number with sign operator, must come without tab or space*/
int getop2(char s[]) {
	
	int i, c1, c2;
	// can't be '\n'
	while ((s[0] = c1 = getch()) == ' ' || c1 == '\t');
	s[1] = '\0';

	if (c1 == '+' || c1 == '-') {
		c2 = getch();
		if (!isdigit(c2) && c2 != '.') {
			// '+' or '-' as operator
			ungetch(c2);
			return c1;	
		} 	
		i = 0; 
		s[++i] = c1 = c2;
	} else if (!isdigit(c1) && c1 != '.') return c1; // not a number
	else i = 0;	

	if (isdigit(c1))
		while (isdigit(s[++i] = c1 = getch())); // integer part
	if (c1 == '.')
		while (isdigit(s[++i] = c1 = getch())); // fraction part
	s[i] = '\0';
	if (c1 != EOF)  ungetch(c1);
	return NUMBER;	
}

#define BUFSIZE 100 

char buf[BUFSIZE];  // buffer for ungetch
int bufp = 0;  // next free position in buf

/* get a (possibly pushed-back) character */
int getch(void) {
	return (bufp > 0)? buf[--bufp] : getchar();
}


/* push character back on input */
void ungetch(int c) {
	if (bufp >= BUFSIZE) 
		printf("ungetch: too many characters\n");
	else	buf[bufp++] = c;	
}
