#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void lookupNumber(int** matrix, int value, int* vector){
    //Hint - use the Minfo struct from matrix.h!

    int i = 0, j = 0;
    int pipe_fd[2];
    pipe(pipe_fd);
    for (i = 0; i < ROWS; i++){
        if (fork() == 0){
            close(pipe_fd[0]);
            int count = 0;
            for (j = 0; j < COLUMNS; j++){
                if (matrix[i][j] == value){
                    count++;
                }
            }
            Minfo minfo = {i, count};
            write(pipe_fd[1],&minfo, sizeof(minfo));

            _exit(0);
        }
    }

    int m = 0;
    close(pipe_fd[1]);
    Minfo minfo;
    for(int i = 0; i < ROWS; i++){
        if (read(pipe_fd[0],&minfo,sizeof(minfo)) != 0){
            vector[m] = minfo.ocur_nr;
            m++;
        }
    }
}