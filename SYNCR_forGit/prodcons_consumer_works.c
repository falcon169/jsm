# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

# define BufferSize 10

void *Producer();
void *Consumer();
static int first_empty_slot = 0;
static int last_filled_slot  =0;
int BufferIndex=0;
int *BUFFER;

pthread_cond_t Buffer_Not_Full=PTHREAD_COND_INITIALIZER;
pthread_cond_t Buffer_Not_Empty=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mVar=PTHREAD_MUTEX_INITIALIZER;

int main()
{    
    pthread_t ptid,ctid;
    
    BUFFER=(int *) malloc(sizeof(int) * BufferSize);            
    
    pthread_create(&ptid,NULL,Producer,NULL);
    pthread_create(&ctid,NULL,Consumer,NULL);
    
    pthread_join(ptid,NULL);
    pthread_join(ctid,NULL);
        
    
    return 0;
}

void *Producer()
{    
    for(;;)
    {
        pthread_mutex_lock(&mVar);
        while(BufferIndex == BufferSize)
        {                        
            pthread_cond_wait(&Buffer_Not_Full,&mVar);
        }                        
        BUFFER[first_empty_slot]=rand();
        printf("Produce : %d Value %d \n",first_empty_slot, BUFFER[first_empty_slot]);
        first_empty_slot = (first_empty_slot +1) %BufferSize;
        BufferIndex++;
        pthread_cond_signal(&Buffer_Not_Empty);        
        pthread_mutex_unlock(&mVar);
    }    
    
}

void *Consumer()
{
    int value;
    for(;;)
    {
        pthread_mutex_lock(&mVar);
        while(BufferIndex==0)
        {            
            pthread_cond_wait(&Buffer_Not_Empty,&mVar);
        }                
        value = BUFFER[last_filled_slot];
        printf("Consume : %d Value %d \n",last_filled_slot, value);        
        last_filled_slot = (last_filled_slot+1)%BufferSize;
        BufferIndex--;
        pthread_cond_signal(&Buffer_Not_Full);                
        pthread_mutex_unlock(&mVar);        
    }    
}
