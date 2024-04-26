#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *print_message(void *arg){
    char *msg = (char *)arg;
    printf(" %s\n",msg);
    return NULL;
}

int main(){
    pthread_t thread;
    char *msg = "bonjour tout le monde";
    pthread_create(&thread,NULL,print_message,msg);
    pthread_join(thread,NULL);
    return EXIT_SUCCESS;

}
