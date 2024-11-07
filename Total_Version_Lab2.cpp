#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define N 20

void freeMatrix(int** matrix, int m) {
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int fillMatrix(int** matrix_A, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf_s("%d", &matrix_A[i][j]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}

void printMatrix(int** matrix_A, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix_A[i][j]);
        }
        printf("\n");
    }
}

int findColumnToRemove(int** matrix_A, int m, int n) {
    for (int j = 0; j < n; j++) {
        int isNonPositive = 1;
        int isSorted = 1;
        for (int i = 0; i < m; i++) {
            if (matrix_A[i][j] > 0) {
                isNonPositive = 0;
                break;
            }
            if (i > 0 && matrix_A[i][j] < matrix_A[i - 1][j]) {
                isSorted = 0;
                break;
            }
        }
        if (isNonPositive && isSorted) {
            return j;
        }
    }
    return -1;
}

int transformMatrix(int** matrix_A, int** matrix_B, int m, int n) {
    int colToRemove = findColumnToRemove(matrix_A, m, n);
    if (colToRemove == -1) {
        printf("Столбец для удаления не найден!\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n - 1; j++) {
                matrix_B[i][j] = 0;
            }
        }
        return 0;
    }

    for (int i = 0; i < m; i++) {
        int colIndex = 0;
        for (int j = 0; j < n; j++) {
            if (j != colToRemove) {
                matrix_B[i][colIndex++] = matrix_A[i][j];
            }
        }
    }
    return 1;
}

int main() {
    int** matrix_A;
    int** matrix_B;
    int i, m, n;

    setlocale(0, "");
    printf("Введите количество строк матрицы (не может быть более 20!): ");
    if (scanf_s("%d", &m) != 1) {
        printf("Ошибка: невозможно ввести букву!\n");
        return 1;
    }
    if (m <= 0) {
        printf("Ошибка: количество строк должно быть положительным числом!\n");
        return 1;
    }

    printf("Введите количество столбцов матрицы (не может быть более 20!): ");
    if (scanf_s("%d", &n) != 1) {
        printf("Ошибка: невозможно ввести букву!\n");
        return 1;
    }
    if (n <= 0) {
        printf("Ошибка: количество столбцов должно быть положительным числом!\n");
        return 1;
    }

    if (m > N || n > N) {
        printf("Размеры матрицы не могут быть больше %d!\n", N);
        return 1;
    }

    matrix_A = (int**)malloc(m * sizeof(int*));
    for (i = 0; i < m; i++) {
        matrix_A[i] = (int*)malloc(n * sizeof(int));
    }
    matrix_B = (int**)malloc(m * sizeof(int*));
    for (i = 0; i < m; i++) {
        matrix_B[i] = (int*)malloc((n - 1) * sizeof(int));
    }

    printf("Введите значения матрицы:\n");
    if (!fillMatrix(matrix_A, m, n)) {
        printf("Матрица может содержать только целые числа!\n");
        freeMatrix(matrix_A, m);
        freeMatrix(matrix_B, m);
        return 1;
    }

    printf("Матрица A:\n");
    printMatrix(matrix_A, m, n);

    if (transformMatrix(matrix_A, matrix_B, m, n)) {
        printf("Матрица B:\n");
        printMatrix(matrix_B, m, n - 1);
    }
    else {
        printf("Матрица B (пустая):\n");
        printMatrix(matrix_B, m, n - 1);
    }

    freeMatrix(matrix_A, m);
    freeMatrix(matrix_B, m);

    return 0;
}