#include<stdio.h> 
#include<pthread.h> 
#include<semaphore.h> 
int buf[5],f,r; 
sem_t mutex,full,empty; 
void *produce(void *arg) 
{ 
    int i; 
    for(i=0;i<10;i++) 
    {int temp; 
        sem_wait(&empty); 
        sem_wait(&mutex); 
        printf("produced item is %d\n",i); 
        buf[(++r)%5]=i; 
        sleep(1); 
        sem_post(&mutex); 
        sem_post(&full); 
 sem_getvalue(&full,&temp); 
        printf("producer : full %u\n",temp); 
    } 
} 
void *consume(void *arg) 
{ 
        int item,i; 
        for(i=0;i<10;i++) 
        {int temp; 
                sem_wait(&full); 
  sem_getvalue(&full,&temp); 
         printf("consumer : full %u\n",temp); 
                sem_wait(&mutex); 
                item=buf[(++f)%5]; 
                printf("consumed item is %d\n",item); 
                sleep(1); 
                sem_post(&mutex); 
                sem_post(&empty); 
        } 
} 
void main() 
{ 
    pthread_t tid1,tid2; 
    sem_init(&mutex,0,1); 
    sem_init(&full,0,1); 
    sem_init(&empty,0,5); 
    pthread_create(&tid1,NULL,produce,NULL); 
        pthread_create(&tid2,NULL,consume,NULL); 
    pthread_join(tid1,NULL); 
    pthread_join(tid2,NULL); 
} 

