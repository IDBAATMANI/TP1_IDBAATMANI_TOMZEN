#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_func1(void *arg){
    printf("Thread 1 : Bonjour !\n");
    return NULL;
}
void *thread_func2(void *arg){
    printf("Thread 2 : Salut !\n");
    return NULL;
}

int main(){
    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,thread_func1,NULL);
    pthread_join(thread1,NULL);
    pthread_create(&thread2,NULL,thread_func2,NULL);
    pthread_join(thread2,NULL);
    return EXIT_SUCCESS;

}
