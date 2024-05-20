#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define BOLD "\e[1;33m"
#define BOLD_OFF "\e[m"
#define DIM 9
#define POSSIBLE 0
#define INVALID -1

typedef struct box {
    int value;
    int possible[9];
} box;

void print_board(box * board, int dim) {
    for (int j = 0; j < dim * 4 + 1; j++) {
            printf(BOLD "-" BOLD_OFF);
        }
    putchar('\n');
    for (int i = 0; i < dim; i++) {
        printf(BOLD "| " BOLD_OFF);
        for (int j = 0; j < dim; j++) {
            if ((j + 1) % 3 == 0) {
                printf("%d " BOLD "| " BOLD_OFF, board[dim * i + j].value);
            } else {
                printf("%d | ", board[dim * i + j].value); 
            }
        }
        putchar('\n');
        for (int j = 0; j < dim * 4 + 1; j++) {
            if ((i + 1) % 3 == 0) {
                printf(BOLD "-" BOLD_OFF);
            } else {
                printf("-");
            }
        }
        putchar('\n');
    }
}

void print_possible(box * board) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            for (int k = 0; k < DIM; k++) {
                int val = board[i * DIM + j].possible[k];
                printf("%d",  val);
            }
            printf(" ");
        }
        printf("\n");
    }
}

void rehash(int value, int row, int col, box * board) {
    board[row * DIM + col].value = value;
    for (int i = 0; i < DIM; i++) {
        board[row * DIM + i].possible[value - 1] = INVALID;
    }
    for (int i = 0; i < DIM; i++) {
        board[i * DIM + col].possible[value - 1] = INVALID;
    }
    int row_start = (row / 3) * 3;
    int col_start = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[(row_start + i) * DIM + col_start + j].possible[value - 1] = INVALID;
        }
    }
    for (int i = 0; i < DIM; i++) {
        board[row * DIM + col].possible[i] = INVALID; 
    }
}


bool hidden_checker(box * board) {
    int count, p_col;
    for (int row = 0; row < DIM; row++) {
        for (int value = 1; value < 10; value++) {
            count = 0;
            p_col= 0;
            for (int col = 0; col < DIM; col++) {
                if (board[row * DIM + col].value == value) {
                    break;
                } else if (board[row * DIM + col].possible[value - 1] == POSSIBLE) {
                    count++;
                    p_col = col;
                } 
            }
            if (count == 1) {
                rehash(value, row, p_col, board);
                return true;
            }
        }
    }
    return false;
}

bool naked_checker(box * board) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            int count = 0;
            int p_value = 0;
            for (int value = 1; value < 10; value++) {
                if (board[i * DIM + j].possible[value - 1] == POSSIBLE) {
                    count++;
                    p_value = value;
                }
            }
            if (count == 1) {
                rehash(p_value, i, j, board);
                return true;
            }

        }
    }
    return false;
}

void hash_input(box * board, int * input) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if(input[i * DIM + j] != 0) {
                rehash(input[i * DIM + j], i, j, board);
            }
        }
    }
}

bool attempt_solve(box * board) {
    while (hidden_checker(board) || naked_checker(board)) ;
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (board[i * DIM + j].value == 0) {
                return false;
            }
        }
    }
    return true;
}

void solve(int * input) {
    struct timeval start, end;
    box * board = calloc(DIM * DIM, sizeof(box));
    hash_input(board, input);
    printf("Initial Board:\n");
    print_board(board, DIM);
    gettimeofday(&start, NULL);
    printf("Solve: %s\n", attempt_solve(board) ? "SUCCESS" : "FAILURE");
    gettimeofday(&end, NULL);
    print_board(board, DIM);
    int sec = end.tv_sec - start.tv_sec;
    long usec = end.tv_usec - start.tv_usec;
    if (usec < 0) {
        sec--;
        usec+= 1000000;
    }
    printf("Time elapsed: %d seconds %lu microseconds\n", sec, usec);
    free(board);
}

int main() {
    //int input[] = {4,3,5,2,6,9,7,8,1,0,8,2,5,7,1,4,9,3,1,9,7,8,3,4,5,6,2,8,2,6,1,9,5,3,4,7,3,7,4,6,8,2,9,1,5,9,5,1,7,4,3,6,2,8,5,1,9,3,2,6,8,7,4,2,4,8,9,5,7,1,3,6,7,6,3,4,1,8,2,5,9};
    int input[] = {0,0,3,0,2,0,6,0,0,9,0,0,3,0,5,0,0,1,0,0,1,8,0,6,4,0,0,0,0,8,1,0,2,9,0,0,7,0,0,0,0,0,0,0,8,0,0,6,7,0,8,2,0,0,0,0,2,6,0,9,5,0,0,8,0,0,2,0,3,0,0,9,0,0,5,0,1,0,3,0,0}; 
    //int input[] = {2,0,0,0,8,0,3,0,0,0,6,0,0,7,0,0,8,4,0,3,0,5,0,0,2,0,9,0,0,0,1,0,5,4,0,8,0,0,0,0,0,0,0,0,0,4,0,2,7,0,6,0,0,0,3,0,1,0,0,7,0,4,0,7,2,0,0,4,0,0,6,0,0,0,4,0,1,0,0,0,3};
    //int input[] = {6,0,0,4,7,0,1,0,2,7,0,0,1,0,0,0,9,0,0,1,0,5,0,8,7,0,4,0,2,0,0,0,0,8,0,0,0,5,0,7,2,6,0,//0,9,4,7,0,0,0,0,0,0,0,0,0,7,0,5,0,0,8,0,0,4,0,0,0,0,0,1,5,0,0,0,9,0,0,0,2,0};
    //int input[] = {0,0,7,0,3,0,0,9,6,0,0,4,1,0,0,0,5,0,3,9,0,0,0,5,0,0,0,0,0,0,0,7,8,9,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,6,0,3,0,4,6,0,2,0,0,4,0,0,0,0,0,1,0,0,7,0,0,0,5,0,0,0,0,0,8,0,0};
    solve(input);
} 
