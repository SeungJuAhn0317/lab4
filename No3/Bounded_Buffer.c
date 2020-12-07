#include <stdio.h>
#include <stdlib.h>

#define THREAD_NUMBER 5

pthread_mutex_t mutex;
int sum;

void *mutex_thread(void *arg){
    pthread_mutex_lock(&mutex);
    sum +=(int)arg;
    pthread_mutex_unlock(&mutex);

    return arg;
}

int main(int argc, char*argv[]){
    pthread_t tid[THREAD_NUMBER];
    int arg[THREAD_NUMBER];
    void *result;
    int status;
    int i = 0;
    if(argc <6){
        fprintf(stderr,"Usage : mutexthread 1,2,3,4,5\n");
        exit(1);
    }
    for(i = 0;i<THREAD_NUMBER;i++){
        arg[i] = atoi(argv[i+1]);
    }
    pthread_mutex_init(&mutex,NULL);
    for(i = 0; i<THREAD_NUMBER;i++){
        status = pthread_create(&tid[i],NULL,mutex_thread,(void*)arg[i]);
        if(status !=0){
            exit(1);
        }
    }
    for (i = 0; i < THREAD_NUMBER; i++) {
        status = pthread_join (tid[i], &result);
        if (status != 0) {
            fprintf (stderr, "Join thread %d: %d", i, status);
            exit (1);
        }
    }
    status = pthread_mutex_destroy (&mutex);
    if (status != 0)
        perror ("Destroy mutex");
    printf ("sum is %d\n", sum);
    pthread_exit (result);
}


