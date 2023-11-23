#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3

int num_values;
int *values;
double average;
int minimum;
int maximum;

// Function to calculate average
void *calculate_average(void *param) {
    double sum = 0.0;
    for (int i = 0; i < num_values; i++) {
        sum += values[i];
    }
    average = sum / num_values;
    pthread_exit(NULL);
}

// Function to calculate minimum
void *calculate_minimum(void *param) {
    minimum = values[0];
    for (int i = 1; i < num_values; i++) {
        if (values[i] < minimum) {
            minimum = values[i];
        }
    }
    pthread_exit(NULL);
}

// Function to calculate maximum
void *calculate_maximum(void *param) {
    maximum = values[0];
    for (int i = 1; i < num_values; i++) {
        if (values[i] > maximum) {
            maximum = values[i];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
        return 1;
    }

    num_values = argc - 1;
    values = (int *)malloc(num_values * sizeof(int));

    for (int i = 0; i < num_values; i++) {
        values[i] = atoi(argv[i + 1]);
    }

    pthread_t threads[NUM_THREADS];

    pthread_create(&threads[0], NULL, calculate_average, NULL);
    pthread_create(&threads[1], NULL, calculate_minimum, NULL);
    pthread_create(&threads[2], NULL, calculate_maximum, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("The average value is %.2lf\n", average);
    printf("The minimum value is %d\n", minimum);
    printf("The maximum value is %d\n", maximum);

    free(values);

    return 0;
}
