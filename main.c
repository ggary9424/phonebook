#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL
#include "memorypool.h"

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}
#define testNum 99;
int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

#if OPT==0
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;
#else
    entry **pHead_array;
    entry **entry_array;
    init_hash_table(&pHead_array, &entry_array);
#endif

#if OPT==2
    //m_pool *mp = (mem_pool *)malloc(sizeof(mp));
    //it_memory_pool(mp);
    int handle = mpInit(sizeof(entry)*400000);
#endif

#if (__GNUC__)
#if OPT==0
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
#endif

    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
#if OPT==0
        e = append(line, e);
#elif OPT==1
        append(line, entry_array);
#elif OPT==2
        append(line, entry_array, handle);
#endif
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
#if OPT==0
    e = pHead;
#endif

#if OPT==0
    assert(findName(input, e) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, e)->lastName, "zyxel"));
#else
    assert(findName(input, pHead_array) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, pHead_array)->lastName, "zyxel"));
#endif

#if defined(__GNUC__)
#if OPT==0
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);

#if OPT==0
    findName(input, e);
#else
    findName(input, pHead_array);
#endif
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    FILE *output;

#if OPT==2
    output = fopen("opt2.txt", "a");
#elif OPT==1
    output = fopen("opt.txt", "a");
#elif OPT==0
    output = fopen("orig.txt", "a");
#endif
    printf("struct entry size = %d\n", sizeof(entry));
    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %.10lf sec\n", cpu_time2);

#if OPT==2
    mpFree(handle);
#endif

    //TODO: free memory you malloc
    //if (pHead->pNext) free(pHead->pNext);
    //free(pHead);

    return 0;
}
