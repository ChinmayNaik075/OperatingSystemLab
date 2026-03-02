#include <stdio.h>

int main() {
    int r, c;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &r, &c);

    int matrix[r][c];

    printf("Enter matrix elements:\n");
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Row sums
    for(int i = 0; i < r; i++) {
        int rowSum = 0;
        for(int j = 0; j < c; j++) {
            rowSum += matrix[i][j];
        }
        printf("Sum of row %d = %d\n", i + 1, rowSum);
    }

    // Column sums
    for(int j = 0; j < c; j++) {
        int colSum = 0;
        for(int i = 0; i < r; i++) {
            colSum += matrix[i][j];
        }
        printf("Sum of column %d = %d\n", j + 1, colSum);
    }

    return 0;
}