#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "murmur3.c"
#include "superfasthash.c"

typedef struct item{
    char* kMer;
    int nCount;
    struct item* next;
} item;

int nCollisions;
int nSeed;

void insertItem(item** head, char* key) {
    item* newItem = (item*) malloc(sizeof(item));
    newItem->kMer = malloc(strlen(key) + 1);
    strcpy(newItem->kMer,key);
    newItem->nCount = 1;
    newItem->next = NULL;

    if(*head == NULL) {
        *head = newItem;
    }
    else {
        item* currItem = *head;

        while(currItem->next != NULL) {
            currItem= currItem->next;
        }
        currItem->next = newItem;
    }
}

item** createTable(int nSize) {
    int i = 0;
    item** hT = (item**) calloc (sizeof(item*),nSize);
    for(i = 0; i < nSize; i++)
        hT[i] = NULL;
    return hT;
}

int getMurmurHashIndex(char* key, int nSize) {
    int index;
	MurmurHash3_x64_128(key,strlen(key),nSeed,&index);
	index = abs(index % nSize);
    return index;
}


int getSuperFastHashIndex(char* key, int nSize) {
    int index = abs(hash(key,strlen(key)) % nSize); 
    return index;
}

item* search(item** hashTable, char *key, int nSize, int index) {
    item* tempItem = hashTable[index];

    if (tempItem == NULL) {
        return NULL;
    }

    while (tempItem != NULL) {
        if(strcmp(tempItem->kMer,key) == 0) {
            return tempItem;
        }
        tempItem = tempItem->next;
    }
}

void insertToTable(item** hashTable, char* key, int nSize) {
   int index = getMurmurHashIndex(key,nSize);
   //int index = getSuperFastHashIndex(key,nSize);
    item* head;

    head = search(hashTable,key,nSize,index);
    if(head != NULL)
    {
        head->nCount++;
        return;
    }

    if(hashTable[index] == NULL)
    {
        head = NULL;
        insertItem(&head,key);
    }
    else 
    {
        head = hashTable[index];
        insertItem(&head,key);
        nCollisions++;
    }

    hashTable[index] = head;
}

char* randString (int n)
{
	int i, nLen = (int) pow(10, (double) n);
	char* cStr, cACGT[4] = {'a', 'c', 'g', 't'};
	srand(time(NULL));
	cStr = (char*) malloc(nLen + 1);
		
	for (i = 0; i < nLen; i++)
		*(cStr + i) = cACGT[rand() % 4];
	*(cStr + nLen) = '\0';
	
	return cStr;
}

char* strOfKLen (char str[], int k)
{
	int i;
	char* cStr;
	cStr = (char*) malloc(k + 1);
	
	strncpy(cStr, str, k);
	cStr[k] = '\0';
	return cStr;
}

int getPrimeNumber(int num) {
    int count = -1, prime = num;

    while(count != 0) {  
        count = 0;    
        for(int i = 2; i < num; i++) {
            if(prime % i == 0)
                count++;
        }
        if(count != 0)
            prime++;
    } 
    return prime;
}

int main(void)
{
	int i, j, x, nSize, n[] = {4, 5, 6}, k[] = {5, 6, 7};	
    srand(time(NULL));
    nSeed = rand();
	
	printf("\nUsing MURMURHASH3 Hash Function\n\n");
    //printf("Using SUPERFASTHASH Hash Function\n\n");

	for(i = 0; i < 3; i++)
	{
		printf("=>  Hash Table Test of n = 10^%i  <=\n", n[i]);
		char* str = randString(n[i]);
		
		for (j = 0; j < 3; j++)
		{
            nCollisions = 0;
            nSize = getPrimeNumber(pow(4, k[j] + 1));
			item** table = createTable(nSize);

			clock_t begin = clock();
			
			for (x = 0; x < strlen(str) - k[j] + 1; x++)
                insertToTable(table,strOfKLen(str + x, k[j]),nSize);

			clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			printf("%i. k = %i [TIME TAKEN]: %fs\n", j + 1, k[j], time_spent);
            printf("\tTotal Collisions:%i\n",nCollisions);
		}
		printf("\n\n");
		free(str);
	}	
	return 0;
}





