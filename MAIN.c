#include <stdio.h>
#define MAXN 10000
#define MAXK 100
#include "COMPARE.c"
#include "doalg.c"
main(){
	int N[2] = {100,10000};
	int K[2] = {10,40};
	int Best[MAXK];
	int k,n,flag,round,ct,loop,biggest,total;

	for (round=0; round<1; round++) {//CHANGED FROM round<2 to round<1
		total = 0;
		biggest = -1;
		for (loop=0; loop<1000; loop++) {//CHANGED FROM loop<1000 TO loop<1
			n = N[round];      //round = 0 so n = 100 ==> round = 1 so n = 10000
							   // 10 <= n <= 10000
			k = K[round];	   //round = 0 so k = 10  ==> round = 1 so k = 40
							   // 1 <= k <= 100
			n = 10000;			   //CHANGED N -------------------
			k = 10;			   //CHANGED K -------------------
			COMPARE(0,n);	   //initializes a private array (indexed from 1 to n), w/ random distinct values
							   //returns 0 normally, otherwise -1 if n is out of range. (10 <= n <= 10000)
							   //round = 0 ==> COMPARE(0,100) // round = 1 ==> COMPARE(0,10000)
							   //
							   //This function will setup a private array => static int number[...]
							   //that exists so that when we call COMPARE(index1, index2) it uses those indexes
							   //to return 1 (number[ind1] > number[ind2])
							   //to return 2 (number[ind2] > number[ind1])
							   //to return -1 if indexes are out of range
			//printf("About to enter the doalg function\n");
			flag = doalg( n, k, Best);
			//printf("Came out of the doalg  function\n");
			//doalg(...) will generate the values for the int array called Best
			//returns 1 if no errors, otherwise returns 0
			if (flag==0) {
				printf(" *** flagged error at loop=%d\n",loop);
				return(0);
			}
			ct = COMPARE(-1,k,Best);
			//this will verify that the elements in Best are correct and in order
			//returns the comparisons made if Best[] is correct
			//returns a negative value if there were any errors
			if (ct<=0) {
				printf(" *** error at loop=%d\n",loop);
				return(0);
			}
			if (ct>biggest) biggest=ct;
			total += ct;
		}
		printf("n=%5d,  k=%d:  maximum= %d,  avg=%8.2f\n",
			N[round],K[round],biggest,(1.0*total)/1000);
		fflush(stdout);
	}
}
