#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10  // Taille du tableau
#define NUM_THREADS 4   // Nombre de threads

int totalSum = 0;

typedef struct {
    int *start;
    int *end;
    pthread_mutex_t *lock;
} PartialSumArgs;

void *sum_partial(void *args) {
    PartialSumArgs *partialArgs = (PartialSumArgs *)args;

    int partialSum = 0;

    // Calcul de la somme partielle
    int *p;
    for (p = partialArgs->start; p < partialArgs->end; p++) {
        partialSum += *p;
    }

    // Verrouillage de la section critique
    pthread_mutex_lock(partialArgs->lock);

    // Ajout de la somme partielle à la somme totale
    totalSum += partialSum;

    // Déverrouillage de la section critique
    pthread_mutex_unlock(partialArgs->lock);

    pthread_exit(NULL);
}

int main() {
    int array[ARRAY_SIZE];
    int i;

    // Initialisation du tableau
    for (i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    // Initialisation du mutex
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);

    // Création des threads et des arguments
    pthread_t threads[NUM_THREADS];
    PartialSumArgs threadArgs[NUM_THREADS];

    int sectionSize = ARRAY_SIZE / NUM_THREADS;
    for (i = 0; i < NUM_THREADS; ++i) {
        // Configuration des arguments pour chaque thread
        threadArgs[i].start = (array + i * sectionSize);
        threadArgs[i].end = (array + ((i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * sectionSize));
        threadArgs[i].lock = &lock;

        // Création du thread et vérification des erreurs
        if (pthread_create(&threads[i], NULL, sum_partial, (void *)&threadArgs[i]) != 0) {
            fprintf(stderr, "Erreur lors de la création du thread %d\n", i);
            return 1;
        }
    }

    // Attente de la fin de chaque thread
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Affichage de la somme totale
    printf("Somme totale : %d\n", totalSum);

    // Destruction du mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
