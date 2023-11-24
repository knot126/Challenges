#include <stdio.h>
#include <math.h>

const char *NAMES[] = {"Sheldon", "Leonard", "Penny", "Rajesh", "Howard"};

/**
 * Solve the double cola problem.
 * 
 * https://codeforces.com/problemset/problem/82/A
 * 
 * Notice that the line "cycles" and that the number of times a each person
 * appears is equal to the cycle count (plus one depending on how you index):
 * 
 * Cycle #     Appearances   Example of line at start of cycle
 * 0           0             
 * 1           1             0 1 2 3 4
 * 2           2             0 0 1 1 2 2 3 3 4 4
 * 3           3             0 0 0 0 1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4
 * 
 * We want to find who is at the 1st position in the queue for some N amount
 * of people who have visited.
 * 
 * First, I want to imagine that we know we're in the Cth cycle with some offset
 * into it K as the person who is currently first in the queue.
 * 
 *    C = 2, K = 3
 * 0 0 1 1 2 2 3 3 4 4
 *       ^
 * 
 * Notice that in this limited case we could calculate the Nth person's id as:
 * 
 * N = floor(K / 2^C)
 * 
 * (Since C grows expontentially according to powers of two since each cycle 
 * the number of people getting doubled is double the previous cycle.)
 */

int calcNfromCK(int c, int k) {
	return k / pow(2, c); // integer division in c floors for us
}

/**
 * This simplifies the problem, since now all we need to do is to convert the
 * general problem into this simpler problem. Thankfully this can be done
 * somewhat easily, since finding C and K is kind of like a special version of
 * division where the divisor grows expontentially each iteration:
 */

void findCK(int n, int *c_out, int *k_out) {
	int c = 1, k;
	
	// Remove the amount of people of the previous queue if there is enough
	// left, otherwise we stop and what is left of n is our "remainder" k.
	while ((n - 5 * pow(2, c)) >= 0) {
		n -= 5 * pow(2, c);
		c += 1;
	}
	
	k = n;
	
	c_out[0] = c, k_out[0] = k;
}

/** 
 * Now we can combine these together.
 */

int main(int argc, const char *argv[]) {
	int number;
	
	printf("Place (from 1) of person you want to find: ");
	scanf("%d", &number);
	
	if (number == 0) {
		for (int n = 0; n < 100; n++) {
			int c, k;
			
			findCK(n, &c, &k);
			int result = calcNfromCK(c, k);
			
			printf("%d  ->  %d (c = %d; k = %d; %s)\n", n, result, c, k, NAMES[result]);
		}
		
		return 0;
	}
	
	number -= 1; // convert to proper indexes
	
	printf("\n");
	
	int c, k;
	
	findCK(number, &c, &k);
	int result = calcNfromCK(c, k);
	
	printf("Answer: %d (c = %d; k = %d; %s)\n", result, c, k, NAMES[result]);
	
	return 0;
}
