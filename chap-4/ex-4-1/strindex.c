/* Exercise 4-1.Write the function strindex(s,t)which returns the position of the rightmostoccurrence of tin s, or -1 if there
is none. */

#include <stdio.h>
#include <string.h>

int strindex(char*, char *);
int strindex_rm(char *, char *);

int main(void) {


	char *text[] = {"this is some text isn't it?", "ABEABABABABD ABCFGABC", "\tABCdefABC ABABCHi\nABCABd", " dd", ""};
	char *pattern[] = {"is", "ABC", "ABC", "", ""};
	int len = sizeof(text) / sizeof(text[0]);	
	char * eachtext;	
	char * eachpattern;
	int res;
	int i;
	for (i = 0; i < len; i++) {
	
		eachtext = text[i];
		eachpattern = pattern[i];
	
		printf("Test #%d\nFIND PATTERN FROM LEFT TO RIGHT:\n", i);
		res = strindex(eachtext, eachpattern);
		if (-1 != res) 
			printf("Raw text \"%s\"\nPattern \"%s\" at index: %d\nThe string that starts the pattern is: \n%s\n\n",
			eachtext, eachpattern, res, eachtext + res);
		else	printf("Raw text \"%s\"\nPattern \"%s\" not found\n\n", eachtext, eachpattern);
		printf("FIND PATTERN FROM RIGHT TO LEFT:\n");
		res = strindex_rm(eachtext, eachpattern);
		if (-1 != res) 
			printf("Raw text \"%s\"\nPattern \"%s\" at index: %d\nThe string that starts the pattern is: \n%s\n\n",
			eachtext, eachpattern, res, eachtext + res);
		else	printf("Raw text \"%s\"\nPattern \"%s\" not found\n\n", eachtext, eachpattern);
	}
	return 0;
}



/* return the start index of t in s, -1 on not found */
int strindex(char *s, char *t) {
	
	int s_ind, t_ind; 
	int s_ind_cp;	
	for (s_ind = 0; s[s_ind] != '\0'; s_ind++) {
		s_ind_cp = s_ind;
		t_ind = 0;
		while (t[t_ind] != '\0' && t[t_ind] == s[s_ind_cp]) {
			t_ind++;
			s_ind_cp++;
		}
		if (t[t_ind] == '\0')	return s_ind;
	}
	return -1;		
}


/* return the rightmost occurrence *t in *s, -1 on not found */
int strindex_rm(char *s, char *t) {
	int s_ind, t_ind;
	int s_ind_cp;
	
	for (s_ind = strlen(s) - 1; s_ind >= 0; s_ind--) {
		
		s_ind_cp = s_ind;
		t_ind = strlen(t) - 1;
		while (t_ind >= 0 && s[s_ind_cp] == t[t_ind]) {
			t_ind--;
			s_ind_cp--;
		}
		if (t_ind < 0)	return s_ind - strlen(t) + 1;
	}
	return -1;
}
