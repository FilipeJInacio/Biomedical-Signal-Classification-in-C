#include "parser.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



unsigned short* readBinaryFile(const char* filename, size_t* numNumbers) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return NULL;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("Error getting file size");
        close(fd);
        return NULL;
    }

    // Calculate the number of numbers in the file
    *numNumbers = sb.st_size / sizeof(unsigned short);

    // Map the file into memory
    unsigned short* numbers = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (numbers == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return NULL;
    }

    // Close the file descriptor
    close(fd);

    return numbers;
}


