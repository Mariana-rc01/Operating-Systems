#include "matrix.h"


int** createMatrix() {

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

// ex.5
int valueExists(int** matrix, int value) {
    int i = 0, j = 0;
    int flag = 255;
    pid_t child_pid;
    int status;
    for (i = 0; i < ROWS; i++){
        if ((child_pid = fork()) == 0){
            for (j = 0; j < COLUMNS; j++){
                if (matrix[i][j] == value){
                    flag = i;
                }
            }
            _exit(flag);
        }
    }
    
    for (i = 0; i < ROWS; i++){
        pid_t wait_pid = wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 255){
            flag = WEXITSTATUS(status);
        }
    }

    return flag;
}

// ex.6
void linesWithValue(int **matrix, int value) {

    int i = 0, j = 0;
    int flag = 255;
    pid_t child_pid;
    pid_t pids[ROWS];
    int status;
    for (i = 0; i < ROWS; i++){
        if ((child_pid = fork()) == 0){
            for (j = 0; j < COLUMNS; j++){
                if (matrix[i][j] == value){
                    flag = i;
                }
            }
            _exit(flag);
        }
        else{
            pids[i] = child_pid;
        }
    }
    int m = 0;
    for (i = 0; i < ROWS; i++){
        pid_t wait_pid = waitpid(pids[i],&status,0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 255){
            printf("Encontrou %d\n", WEXITSTATUS(status));
        }
    }
}