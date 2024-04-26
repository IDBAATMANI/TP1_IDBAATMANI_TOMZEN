#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define NUM_TACHE 3

typedef struct {
    int id;
    int period;
} PeriodicTask;

void *taskFunction(void *arg) {
    PeriodicTask *task = (PeriodicTask *)arg;
    int oldstate;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    while (1) {
        sleep(task->period);
        printf("Tache %d \n", task->id);
        pthread_testcancel(); // Permettre l'annulation à ce point
    }
    return NULL;
}

int main() {
    PeriodicTask task[NUM_TACHE] = {
        {1, 1},
        {2, 2},
        {3, 3}
    };

    pthread_t threads[NUM_TACHE];

    // Création des threads pour exécuter les tâches périodiques
    for (int i = 0; i < NUM_TACHE; i++) {
        pthread_create(&threads[i], NULL, taskFunction, &task[i]);
    }

    // Attente de quelques secondes avant d'annuler les threads
    sleep(10);

    // Annulation des threads
    for (int i = 0; i < NUM_TACHE; i++) {
        pthread_cancel(threads[i]);
    }

    // Attente de la terminaison des threads
    for (int i = 0; i < NUM_TACHE; i++) {
        pthread_join(threads[i], NULL);
    }

    return EXIT_SUCCESS;
}
