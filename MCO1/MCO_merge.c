#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 65536

void merge(int Arr[], char cStr[], int nLeft, int nMid, int nRight)
{
    int i, j, k;
    int nLenL = nMid - nLeft + 1;
    int nLenR = nRight - nMid;
    int L[nLenL], R[nLenR];

    for (i = 0; i < nLenL; i++)
    	L[i] = Arr[nLeft + i];
        
    for (j = 0; j < nLenR; j++)
    	R[j] = Arr[nMid + j + 1];

    i = j = 0;
    for (k = nLeft; k < nRight && i < nLenL && j < nLenR; k++)
    {
    	if (strcmp(cStr + L[i], cStr + R[j]) <= 0)
    	{
    		Arr[k] = L[i];
    		i++;
		}
		else
		{
			Arr[k] = R[j];
			j++;
		}
	}
	
	while (i < nLenL)
	{
    	Arr[k] = L[i];
    	k++;
    	i++;
	}
	
	while (j < nLenR)
	{
		Arr[k] = R[j];
		k++;
		j++;
	}
	
}

void mergeSort(int Arr[], char cStr[], int p, int r)
{
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(Arr, cStr, p, q);
        mergeSort(Arr, cStr, q + 1, r);
        merge(Arr, cStr, p, q, r);
    }
}

char* randString (int n)
{
	int i;
	char* cStr, cACGT[4] = {'a', 'c', 'g', 't'};
	srand(time(NULL));
	cStr = (char*) malloc(n + 1);
	
	for (i = 0; i < n; i++)
		*(cStr + i) = cACGT[rand() % 4];
	*(cStr + n) = '\0';
	
	return cStr;
}

int main (void)
{
	int i, j;
	int suffArr[MAX], nTest[10] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};
	double fAve;
	
	for(i = 0; i < MAX; i++)
		suffArr[i] = i;
		
	for (i = 0; i < 10; i++)
	{
		fAve = 0;
		printf("[%i]\t", nTest[i]);
		for(j = 0; j < 1000; j++)
		{
			clock_t begin = clock();
			mergeSort(suffArr, randString(nTest[i]), 0, nTest[i] - 1);
			clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			fAve += time_spent;
		}
		fAve /= 1000;
		printf("AVERAGE: %lf\n", fAve);
	}
	
}

