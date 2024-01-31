#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct node {
    char *kMer;
    int nCount;
    struct node *pLeft;
    struct node *pRight;
} node;

void create(struct node **node) {
	(*node) = NULL;
}

void insert(char* key, struct node** node)
{
    int nRes;
    if((*node) == NULL)
	{
        (*node) = (struct node*) malloc(sizeof(struct node) + (strlen(key) + 1));
        (*node)->kMer = malloc(strlen(key) + 1);
        strcpy ((*node)->kMer, key);
        (*node)->pLeft = NULL;
        (*node)->pRight = NULL;
        (*node)->nCount = 1;
    }
	else
	{
        nRes = strcmp(key, (*node)->kMer);
        
        if (nRes < 0)
            insert(key, &(*node)->pLeft);
        else if (nRes > 0)
            insert(key, &(*node)->pRight);
        else
        	((*node)->nCount)++;
    }
}

struct node* search(char* key, struct node** node)
{
	if ((*node) == NULL || strcmp((*node)->kMer, key) == 0)
		return (*node);
	else if (strcmp((*node)->kMer, key) > 0)
		return search(key, &(*node)->pLeft);
	else
		return search(key, &(*node)->pRight);
}

void deleteTree(node** node)
{
	if ((*node) != NULL)
	{
		if (((*node)->pLeft) != NULL)
	    	deleteTree(&(*node)->pLeft);
	    	
	    if (((*node)->pRight) != NULL)
	    	deleteTree(&(*node)->pRight);
	    
	    free((*node)->kMer);
	    free((*node));
	}
}

void preOrder(struct node *node)
{
    if(node != NULL)
	{
        printf("%s:\t%i\n", node->kMer, node->nCount);
        preOrder(node->pLeft);
        preOrder(node->pRight);
    }
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

int main(void)
{
	
	int i, j, x, n[] = {4, 5, 6}, k[] = {5, 6, 7};
	
	
	for (i = 0; i < 3; i++)
	{
		printf("=>  Binary Search Tree Test of n = 10^%i  <=\n", n[i]);
		char* str = randString(n[i]);
		
		for (j = 0; j < 3; j++)
		{
			clock_t begin = clock();
			
			
			node *root;
			
			create(&root);
			
			for (x = 0; x < strlen(str) - k[j] + 1; x++)
				insert(strOfKLen(str + x, k[j]), &root);
			
			
			clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			printf("%i. k = %i [TIME TAKEN]: %fs\n", j + 1, k[j], time_spent);
			
			deleteTree(&root);			
		}
		printf("\n\n");
		free(str);
	}	
	return 0;
}
