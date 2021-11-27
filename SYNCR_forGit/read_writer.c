#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* the number of reader threads */
#define READERS 16

/* the number of writer threads */
#define WRITERS 16

/* the number of times the threads loop */
#define LOOPS 10000

/* the size of the linked list */
#define DATA_SIZE 10000

/* the largest item in the list */
#define MAX_VALUE 100000

/* whether we are doing the read/write lock */
#define READ_WRITE 1
#define MUTEX 0
#define UNLOCKED 0
/* declare either a mutex or a read/write lock */

#if READ_WRITE
pthread_rwlock_t lock;
#elif MUTEX
pthread_mutex_t lock;
#elif UNLOCKED

#endif

/* a linked list node */
struct node_t {
    int data;
    struct node_t* next;
};

/* add an element at front of list */
void list_insert(struct node_t** head, int data) {
    struct node_t* new = malloc(sizeof(struct node_t));
    new->data = data;
    new->next = *head;
    *head = new;
}

/* check if an element is in the list */
int list_member(struct node_t* head, int data) {
    struct node_t* current = head;
    while (current) {
        if (current->data == data) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/* remove the first instance of an element from a list */
void list_remove(struct node_t** head, int data) {
    struct node_t* previous = NULL;
    struct node_t* current = *head;
    while (current) {
        if (current->data == data) {
            if (previous) {
                previous->next = current->next;
            } else {
                *head = current->next;
            }
            free(current);
            return;
        }
        current = current->next;
    }
}

/* print a linked list to the screen */
void list_print(struct node_t* head) {
    struct node_t* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/* our list is global */
struct node_t* head = NULL;

/* thread function which inserts and removes elements */
void* writer(void* idp) {
    /* continually insert and remove items */
    unsigned int seed = 0;
    while(1) {
        /* lock it */
#if READ_WRITE
        pthread_rwlock_wrlock(&lock);
#elif MUTEX
        pthread_mutex_lock(&lock);
#else
#endif
        /* modify the list */
        int value = rand_r(&seed) % MAX_VALUE;
        list_insert(&head, value);
        list_remove(&head, value);

        /* unlock it */
#if READ_WRITE
        pthread_rwlock_unlock(&lock);
#elif MUTEX
        pthread_mutex_unlock(&lock);
#elif UNLOCKED

#endif
    }

    pthread_exit(NULL);
}

/* thread function which tests if elements are in the list */
void* reader(void* idp) {
    /* continually print the list */
    int count = 0;
    unsigned int seed = 0;
    for (int i = 0; i < LOOPS; i++) {
        /* lock it */
#if READ_WRITE
        pthread_rwlock_rdlock(&lock);
#elif MUTEX
        pthread_mutex_lock(&lock);
#elif UNLOCKED
#endif

        /* check if a random node is in the list */
        count += list_member(head, rand_r(&seed) % MAX_VALUE);

        /* unlock it */
#if READ_WRITE
        pthread_rwlock_unlock(&lock);
#elif MUTEX
        pthread_mutex_unlock(&lock);
#elif UNLOCKED

#endif
    }

    printf("Count = %d.\n", count);

    pthread_exit(NULL);
}

int main() {
    /* an array of reader and writer threads */
    pthread_t readers[READERS];
    pthread_t writers[WRITERS];

    /* initialize the lock */
#if READ_WRITE
    printf("Using a read-write lock:\n");
    pthread_rwlock_init(&lock, NULL);
#elif MUTEX
    printf("Using a mutex:\n");
    pthread_mutex_init(&lock, NULL);
#elif UNLOCKED
#endif

    /* put random data into the list */
    for (int i = 0; i < DATA_SIZE; i++) {
        list_insert(&head, rand() % MAX_VALUE);
    }

    /* spawn all threads */
    for (int i = 1; i < READERS; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }
    for (int i = 1; i < WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    /* join all readers */
    for (int i = 1; i < READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    return 0;
}

