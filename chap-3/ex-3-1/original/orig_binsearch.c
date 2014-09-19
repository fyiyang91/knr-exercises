/* Exercise 3-1.Our binary search makes two tests inside the loop, when one would suffice 
(at the price of more tests outside.) Write a version with only one test inside the loop 
and measure the difference in run-time.  

This is the original binsearch function */

#include <stdio.h>
#define LEN 65535 

int binsearch(int, int *, int);
static void eval(int, int);

/* simple test client */
int main(void) {

	
	int testarr[LEN];
	int queryarr[LEN];
	int i, res;	

	for (i = 0; i < LEN; i++) {
		testarr[i] = 3 * i + 2;
		queryarr[i] = i;
	} 	
	for (i = 0; i < LEN; i++) {
		res = binsearch(queryarr[i], testarr, LEN);
		eval(queryarr[i], res);
	}	
	return 0;
}


/* binary serach, find x in array v[] of length n, return index on success, -1 on failure */
int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
	else if (x > v[mid]) 
	    low = mid + 1;
	else
	    return mid;
    }    
    return -1;
}

/* help function */
void eval(int query, int res) {
	if (-1 == res)	printf("%d not found\n", query);
	else	printf("%d found at index %d\n", query, res);	
}

