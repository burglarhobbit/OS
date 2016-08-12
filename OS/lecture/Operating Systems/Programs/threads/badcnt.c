#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

#define NITERS 200000000
void *count(void *arg);
/* shared counter variable */
unsigned int cnt = 0;
int main() 
{   pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, count, NULL);
    pthread_create(&tid2, NULL, count, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    if (cnt != (unsigned)NITERS*2)
        printf("Value of cnt variable not proper! cnt=%d\n", cnt);
    else
        printf("OK cnt=%d\n", cnt);
    exit(0);	}
/* thread routine */
void *count(void *arg) 
{   int i;
    for (i = 0; i < NITERS; i++)
        cnt++;
    return NULL;	}
