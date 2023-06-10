#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    unsigned short* numbers;
    size_t start;
    size_t end;
    const char* filename;
} ReadThreadArgs;

void* readThread(void* arg) {
    ReadThreadArgs* args = (ReadThreadArgs*)arg;

    int fd = open(args->filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return NULL;
    }

    size_t fileSize = (args->end - args->start + 1) * sizeof(unsigned short);

    // Map the file portion into memory
    unsigned short* numbers = mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fd, args->start * sizeof(unsigned short));
    if (numbers == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return NULL;
    }

    // Copy the numbers to the shared array
    for (size_t i = 0; i <= args->end - args->start; i++) {
        args->numbers[args->start + i] = numbers[i];
    }

    // Close the file descriptor
    close(fd);

    return NULL;
}

unsigned short* readBinaryFileThreaded(const char* filename, size_t numNumbers) {
    unsigned short* numbers = (unsigned short*)malloc(numNumbers * sizeof(unsigned short));
    if (numbers == NULL) {
        perror("Error allocating memory");
        return NULL;
    }

    size_t numThreads = sysconf(_SC_NPROCESSORS_ONLN);  // Number of available CPU cores
    pthread_t* threads = (pthread_t*)malloc(numThreads * sizeof(pthread_t));
    if (threads == NULL) {
        perror("Error allocating memory");
        free(numbers);
        return NULL;
    }

    ReadThreadArgs* threadArgs = (ReadThreadArgs*)malloc(numThreads * sizeof(ReadThreadArgs));
    if (threadArgs == NULL) {
        perror("Error allocating memory");
        free(numbers);
        free(threads);
        return NULL;
    }

    size_t numbersPerThread = numNumbers / numThreads;
    size_t remainingNumbers = numNumbers % numThreads;

    for (size_t i = 0; i < numThreads; i++) {
        threadArgs[i].numbers = numbers;
        threadArgs[i].start = i * numbersPerThread;
        threadArgs[i].end = (i + 1) * numbersPerThread - 1;
        threadArgs[i].filename = filename;

        if (i == numThreads - 1) {
            // Assign the remaining numbers to the last thread
            threadArgs[i].end += remainingNumbers;
        }

        pthread_create(&threads[i], NULL, readThread, &threadArgs[i]);
    }

    for (size_t i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(threadArgs);

    return numbers;
}