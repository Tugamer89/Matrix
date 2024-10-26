#include "matrix.h"

void print_matrix(double **matrix, size_t n, size_t m) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            printf("%lf ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

void create_matrix(double ***matrix, size_t n, size_t m) {
    *matrix = malloc(n * sizeof(double *));
    for (size_t i = 0; i < n; ++i) {
        (*matrix)[i] = malloc(m * sizeof(double));
        memset((*matrix)[i], 0, m * sizeof(double));
    }
}

void popolate_matrix(double **matrix, size_t n, size_t m) {
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            scanf("%lf", &matrix[i][j]);
}

void swap_rows(double **matrix, size_t a, size_t b) {
    double *tmp = matrix[a];
    matrix[a] = matrix[b];
    matrix[b] = tmp;
}

int main(int argc, char *argv[]) {
    double **A, **b, **X;
    size_t n, dim_A, dim_b;

    // Ask for size and matrix
    printf("Enter size of matrix (n): ");
    scanf("%zu", &n);
    create_matrix(&A, n, n);
    create_matrix(&b, n, 1);
    create_matrix(&X, n, 1);
    
    printf("\nEnter matrix A:\n");
    popolate_matrix(A, n, n);
    printf("\nEnter matrix b:\n");
    popolate_matrix(b, n, 1);

    printf("\nSteps:\n");

    // Gaussian elimination
    for (size_t k = 0; k < n-1; ++k) {
        size_t max_pivot = k;

        for (size_t i = k+1; i < n; ++i)
            if (fabs(A[i][k]) > fabs(A[max_pivot][k]))
                max_pivot = i;

        if (max_pivot != k) {
            printf("Swapping R%zu with R%zu\n", k+1, max_pivot+1);
            swap_rows(A, k, max_pivot);
            swap_rows(b, k, max_pivot);
        }

        double pivot = A[k][k];
        
        if (pivot == 0) {
            printf("Matrix is singular\n");
            return 1;
        }

        for (size_t i = k+1; i < n; ++i) {
            double m = A[i][k] / pivot;
            if (m == 0)
                continue;
            printf("R%zu - %lf*R%zu\n", i+1, m, k+1);
            for (size_t j = 0; j < n; ++j)
                A[i][j] -= m * A[k][j];
            b[i][0] -= m * b[k][0];
        }
    }

    printf("\n");

    // Back subsitution
    X[n-1][0] = b[n-1][0] / A[n-1][n-1];
    for (long long i = n-2; i >= 0; --i) {
        double sum = 0;
        for (size_t j = i+1; j < n; ++j)
            sum += A[i][j] * X[j][0];
        X[i][0] = (b[i][0] - sum) / A[i][i];
    }

    // Print A & b reduced
    printf("A:\n");
    print_matrix(A, n, n);

    printf("b:\n");
    print_matrix(b, n, 1);

    printf("X:\n");
    print_matrix(X, n, 1);

    return 0;
}

/*

1 1 1
0 -1 -1
0 0 -1

*/
