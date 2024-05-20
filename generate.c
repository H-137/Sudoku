#include <stdio.h>
#include <stdlib.h>

#include "generate.h"

int * board;


int check_row(int * board, int row, int col, int dim) {
    for (int i = 0; i < dim; i++) {
        if(board[row * dim + col] == board[row * dim + i]) {
            return 0;
        }
    }
    return 1;
}

int check_col() {
    return 0;
}

int check_box() {
    return 1;
}


void verify_board(int * board, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            
        }
    }
}


// prints_board and uses some logic to determine if a line should be bold for important edges
void print_board(int * board, int dim) {
    for (int j = 0; j < dim * 4 + 1; j++) {
            printf(BOLD "-" BOLD_OFF);
        }
    putchar('\n');
    for (int i = 0; i < dim; i++) {
        printf(BOLD "| " BOLD_OFF);
        for (int j = 0; j < dim; j++) {
            if ((j + 1) % 3 == 0) {
                printf("%d " BOLD "| " BOLD_OFF, board[dim * i + j]);
            } else {
                printf("%d | ", board[dim * i + j]); 
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

int main() {
    board = calloc(DIM * DIM, sizeof(int));
    int practice_board[] = {4,3,5,2,6,9,7,8,1,6,8,2,5,7,1,4,9,3,1,9,7,8,3,4,5,6,2,8,2,6,1,9,5,3,4,7,3,7,4,6,8,2,9,1,5,9,5,1,7,4,3,6,2,8,5,1,9,3,2,6,8,7,4,2,4,8,9,5,7,1,3,6,7,6,3,4,1,8,2,5,9};
    print_board(practice_board, DIM);
    print_board(board, DIM);

    free(board);
    return 1;
}
