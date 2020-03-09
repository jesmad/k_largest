#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

//-----------------------------VERSION 3: Using a Min-Heap  12467 comparisons--------------------------------
/*
 * This algorithm utilizes a min-heap data structure and heap sort in order to obtain the k-largest elements of an array. It follows
 * the following procedure:
 * 		Build a min-heap structure of the first k-elements of an array. (Our array in this case has elements 1, 2, 3,..., n which represent the indices of that COMPARE will use)
 * 		
 * 		After building a min-heap of the first k-elements of the array, compare the root with the other elements of the array (i.e. elements that were not used in our initial construction)
 * 		
 * 		If the element is bigger than the root, replace the root with that element. 
 * 		
 * 		Now that the root is a bigger element and out of place, we need to re-heapify the heap in order to maintain the properties of a min-heap.
 * 		
 * 		We do this for every element starting from array[k+1] to array[n] (assuming array[] contains our list of indices)
 * 		
 * 		After comparing the root with the other elements (n - k times, since there are n-k elements that were not used in our initial construction of the k-element min-heap),
 * 		we will end up with a min-heap of k largest elements. 
 * 		
 * 		Now, we apply heap sort utilizing our heapify function to ensure that the list is in order (ascending order).
 *
 * 		We now have an array called best[] that is in ascending order and contains the indices of the k-largest elements (i.e. index 1 will have the smallest of the largest k-elements)
 *
 * 		Finally we use a function to reorder the best[] array in order to correctly add elements to the Best[] (i.e. in descendnig order)
 *
 * 	Algorithm used was described by a GeeksForGeeks website
 * 	Link: https://www.geeksforgeeks.org/k-largestor-smallest-elements-in-an-array/
 */

void minHeapify(int array[], int index, int sizeArray)
{
	// array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	// 		   {3, 5, 6, 2, 1, 10, 9, 4, 8, 7} = privateArray (seen by COMPARE)
	//
	//***This heapify function was influenced by the C++  binary heap construction presented on a GeeksForGeeks
	//Link: https://www.geeksforgeeks.org/binary-heap/
	int child = 2 * index;			//consider left child						
	int currentParent = array[index];		
	int compareResult;
	
	while (child <= sizeArray)
	{
		//Compare the left and right child, if the left child is bigger ignore it and consider the right child now
		if ( (child < sizeArray) && (compareResult = COMPARE(array[child+1], array[child])) == 2 )
		{
			child++;				//Consider right child now
		}
		//Compare the right child with the parent, if the right child is bigger no swap occurs; otherwise swap.
		if ( (compareResult = COMPARE(currentParent, array[child])) == 2 )
		{
			break;
		}
		//Swapping the parent with the smaller child
		else
		{
			array[child/2] = array[child];
			child = 2 * child;
		}
	}
	
	array[child/2] = currentParent;
	return;
}

void buildHeap(int subArray[], int k)
{
	//This function builds the Min-heap by calling the heapify function
	//parentIndex is k/2 ==> nodes / 2 ==> this will gives us the last parent in the tree (the bottom-most and right-most node that has at least one child (Floyd's Algorithm)
	int parentIndex = k/2;
	for ( ; parentIndex >= 1; parentIndex--)
	{
		minHeapify(subArray, parentIndex, k);
	}
	return;
}

void initArray(int array[], int indexArray, int n)
{
	//Initializes the array with n elements (0,1,2,...,n)
	array[0] = 0;
	for (indexArray = 1; indexArray <= n; indexArray++)
	{	
		array[indexArray] = indexArray;
	}
	return;
}

void initSubArray(int subArray[], int array[], int indexSubArray, int k)
{
	//Initializes the subArray with the first k-elements of array[], so (0,1,2,3,...,k)
	subArray[0] = 0;
	for (indexSubArray = 1; indexSubArray <= k; indexSubArray++)
	{
		subArray[indexSubArray] = array[indexSubArray];
	}
	return;
}

void compareRoot(int indexArray, int indexSubArray, int subArray[], int array[], int n, int k)
{
	//This function compares the root of our Min-Heap (comprised of the first k-elements of array[]
	//with the other elements of array[] starting at index k + 1 and ending at index n.
	//If the root of the Min-Heap is smaller than element array[k+1], array[k+2], ... , or array[n],
	//replace the root with the bigger element and minHeapify the heap starting from the root.
	
	//****This function came about reading a website about finding the largest elements in an array.
	//****Various methods were described we chose to implement the following one (Method 6 from GeeksForGeeks website)
	//****Link: https://www.geeksforgeeks.org/k-largestor-smallest-elements-in-an-array/
	
	int compareResult;
	indexArray = k + 1;				//array[k+1] because we already seen elements array[1], ... , array[k]
	for ( ; indexArray <= n; indexArray++)	
	{
		//If element is larger than the root, replace the root with this element. Heapify the heap so that the parent is smaller than each of its children 
		if ( (compareResult = COMPARE(subArray[indexSubArray], array[indexArray])) == 2) //indexSubArray will always be 1 in this function (i.e. the root index)
		{
			subArray[indexSubArray] = array[indexArray];
			minHeapify(subArray, 1, k);				//Start heapifying from the root (i.e. index 1)
		}
	}
}

void minHeapSort(int best[], int subArray[], int k, int indexSubArray)
{
	//This function takes an array of k-elements that are the k-largest elements in the array in the order of a Min-Heap
	//This function will perform heap sort where the root will be replaced by the last unseen leaf nodes. The resulting array best[]
	//will have the k-largest elements in ascending order.
	int tempK = k;
	int indexBest = 0;											//index of our best[] (NOT Best[])
	int tempValue = subArray[1];
	subArray[1] = subArray[tempK];
	subArray[tempK] = tempValue;

	best[indexBest++] = subArray[tempK];						//add the root to the best[] since its the smallest element in the heap
	tempK--;													//Changing the size of the array so that we don't see nodes that we have already sorted

	for ( indexSubArray = 1; indexSubArray <= k; indexSubArray++)
	{
		minHeapify(subArray, 1, tempK);							//1 because we want to start heapifying from the root, since it was just inserted
		tempValue = subArray[1];								
		subArray[1] = subArray[tempK];
		subArray[tempK] = tempValue;
		best[indexBest++] = subArray[tempK];					//add the root to the best[] (best[] will eventually have a sorted array in ascending order)
		tempK--;
	}
	return;
}

void modifyBest(int best[], int Best[], int k)
{
	//This function takes the array best[] which has the k-largest elements in ascending order and the empty array Best[].
	//Best[] will have the same values as best[] but will have it in the order that we truly want, in descending order.
	int index = 0;
	int j;

	for (j = k - 1; j >= 0; j--)
	{
		Best[index++] = best[j];
	}
	return;
}

int doalg(int n, int k, int Best[])
{
	if ( (n < 10 || n > 10000) || (k < 1 || k > 1000) )
		return 0;

	if ( k > n)
	{
		printf("Error: k cannot be greater than n\n");
		return 0;
	}

	int indexArray = 1;				//This is the starting index
	int array[n+1];					//Create an array of indices starting at index 1 to n (1-based indexing)
	initArray(array, indexArray, n);
		
	int indexSubArray = 1;
	int subArray[k+1];				//Create a subarray of indices from array[1] to array[k] (just the first
									//k-elements of array[]
	initSubArray(subArray, array, indexSubArray, k);

	buildHeap(subArray, k);			//build initial Min-heap of k elements
	
	//compareRoot(...) will modify subArray[] so that it has the k-largest elements of array[]
	//It is represented as a Min-Heap where the root is the smallest element of the k-largest elements
	compareRoot(indexArray, indexSubArray, subArray, array, n, k);
	
	int best[k];					//will contain the k-largest values (associated by indices) in ascending order (smallest to largest)
	minHeapSort(best, subArray, k, indexSubArray);	
	modifyBest(best, Best, k);		//Will modify Best[] by copying the elements of best[] from right to left (descending order)
	
	return 1;
}

/*
//------------------------------ VERSION 1: 399k comparisons---------------------

int indexInBest(int index, int size, int Best[])
{
	//Checks to see whether index is already in the array.
	int i;
	for (i = 0; i < size; i++)
	{
		if (Best[i] == index)
			return 1;		//Index in the array
	}
	return 0;				//Index not in the array
}

int nextiMax(int max, int size, int Best[])
{
	while (indexInBest(max, size, Best))	//while loop breaks when value of max
											//not in Best[]
	{
		max++;								//Looks at value on the right side of max
	}
	return max;
}

int doalg(int n, int k, int Best[])
{
	//Needs error checking, return 0 when values of n and k are out of range 

	int loop;			//loop counter
	int index;			//index of private array
	int iMax;			//index of the current max value
	int i;				//used to intilize Best[]
	int BestIndex = 0;  //index for Best[]

	for (i = 0; i < k; i++) Best[i] = 0; //Initializing the array w/ temp values

	for (loop = 0; loop < k; loop++)
	{
		iMax = 1; //Consider the first element to be the max for now
		iMax = nextiMax(iMax, k, Best);	//Ensures that the current index of the max 
										//element is not in Best[]
		for (index = iMax+1; index <= n; index++)
		{
			//Compares max element with other elements 
			if (indexInBest(index, k, Best))	//If index already in Best[], skip it
				continue;

			int result = COMPARE(iMax, index);
			//If privateArray[index] > privateArray[iMax] ==> iMax = index
			if (result == 2) iMax = index;		
		}
		
		Best[BestIndex++] = iMax;	//Add the index of the max value in Best[]
	}

	//int q;
	//for (q = 0; q < k; q++)
	//{
	//	printf("Best[%d]: %d\n", q, Best[q]);
	//}

	return 1;	
	//------------------------------------------------------------------
}
*/
