#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int readcnt = 0;
pthread_mutex_t counter_lock, write_lock;

void lock_for_writing(void)
{
   pthread_mutex_lock(&write_lock);
}

void unlock_for_writing(void)
{
   pthread_mutex_unlock(&write_lock);
}
//Any number of readers can read..only need to protect the readcnt
void lock_for_reading(void)
{
    pthread_mutex_lock(&counter_lock);
    readcnt++;
    //if am thefirst reader, writers should wait
    if (readcnt == 1) {
        pthread_mutex_lock(&write_lock);
    }
    pthread_mutex_unlock(&counter_lock);
}

void unlock_for_reading(void)
{
    pthread_mutex_lock(&counter_lock);
    readcnt--;
    if (readcnt == 0) {
        //am last reader, writes can write
        pthread_mutex_lock(&write_lock);
    }
    pthread_mutex_unlock(&counter_lock);
}
