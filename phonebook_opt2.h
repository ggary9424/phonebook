#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
//#define APPEND_DATA_SIZE 400000

/* modefy phonebook.h with adding new struct entry1 to decrease entry size ,and then miss cache rate will decrease.*/
// #define OPT 1
typedef struct __PHONE_BOOK_ENTRY_WITHOUT_LASTNAME {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} entry1;

typedef struct __PHONE_BOOK_ENTRY {
    int nodeAllocated;
    char lastName[MAX_LAST_NAME_SIZE];
    entry1 *detail;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

/*
typedef struct __MEMORY_POOL {
	entry *node[APPEND_DATA_SIZE];
	int count;
} mem_pool;
*/
//void init_memory_pool();
entry *findName(char lastname[], entry **pHead);
void append(char lastName[], entry **e, int handle);
void init_hash_table(entry ***e_head, entry ***e);
int hashFunc(char lastName[]);

#endif

