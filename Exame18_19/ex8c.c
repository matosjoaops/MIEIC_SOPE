#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define NB 10
#define F 5
#define NOT_PSHARED 0

int food_bits = 0;
int finish = 0;

sem_t full,empty;

void *bird(void *arg)
{
    while (finish == 0)
    {

        if (food_bits == 0)
        {
            get_food();
            food_bits = F;
        }
        
    }
    return NULL;
}

void *baby(void *arg)
{
    int id = *(int *)arg;
    int n_bits = 0;
    
    while (finish == 0)
    {
        if (food_bits == 0)
        {
            fprintf(stderr,"I am baby %d, I have already eaten %d bits of food and I am still hungry!",id , n_bits);
        }
        else 
        {
            n_bits++;
            food_bits--;
        }
    }
    return NULL;
}

int main(void)
{
    pthread_t tid_bird, tid_baby[NB];

    int ids[NB];

    sem_init(&full,NOT_PSHARED,0);
    sem_init(&empty,NOT_PSHARED,1);

    pthread_create(&tid_bird,NULL,bird,NULL);
    for (int i = 0; i < NB; i++)
    {
        ids[i] = i;
        pthread_create(&tid_baby[i],NULL,baby,&ids[i]);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
}