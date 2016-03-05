#include <stdlib.h>

#include "phonebook_opt2.h"
#include "memorypool.h"

#define BUCKETSIZE 5381

/*
void init_memory_pool(mem_pool *mp){
	int i;
	for(i=0; i<APPEND_DATA_SIZE; i++){
		(mp->node)[i] = (entry *)malloc(sizeof(entry));
		(mp->node)[i]->nodeAllocated=0;
	}
	mp->count=APPEND_DATA_SIZE;
}
*/

entry *findName(char lastName[], entry **pHead)
{
    int key = hashFunc(lastName);
    entry *tmp = *(pHead+key);
    while (tmp != NULL) {
        if (strcasecmp(lastName, tmp->lastName) == 0)
            return tmp;
        tmp = tmp->pNext;
    }
    return NULL;
}

void append(char lastName[], entry **e, int handle)
{
    int key = hashFunc(lastName);
    entry *tmp = *(e+key);
    tmp->pNext = mpAlloc(handle, sizeof(entry));
    strcpy(tmp->lastName, lastName);
    tmp = tmp->pNext;
    tmp->pNext = NULL;
    *(e+key) = tmp;
}

void init_hash_table(entry ***e_head, entry ***e)
{
    *e_head = (entry *)malloc(sizeof(entry *)*BUCKETSIZE);
    *e = (entry *)malloc(sizeof(entry *)*BUCKETSIZE);
    int i=0;
    for(i=0; i<BUCKETSIZE; i++) {
        (*e_head)[i] = (entry *) malloc(sizeof(entry));
        ((*e_head)[i])->pNext = NULL;
        (*e)[i] = (*e_head)[i];
    }
}

int hashFunc(char lastName[])
{
    unsigned long hash = 5381;

    while (*lastName++)
        hash = ((hash << 5) + hash) + (int)*lastName; /* hash * 33 + c */

    return (int)(hash % BUCKETSIZE);
}
