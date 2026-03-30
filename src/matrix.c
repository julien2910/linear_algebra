#include "matrix.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

Matrix* matrix_create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    
    Matrix *m = (Matrix*)malloc(sizeof(Matrix));
    if (!m) return NULL;
    
    m->data = (double**)malloc(rows * sizeof(double*));
    if (!m->data) {
        free(m);
        return NULL;
    }
    
    for (int i = 0; i < rows; i++) {
        m->data[i] = (double*)calloc(cols, sizeof(double));
        if (!m->data[i]) {
            for (int j = 0; j < i; j++) free(m->data[j]);
            free(m->data);
            free(m);
            return NULL;
        }
    }
    
    m->rows = rows;
    m->cols = cols;
    return m;
}

void matrix_free(Matrix *m) {
    if (!m) return;
    
    for (int i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

Matrix* matrix_copy(const Matrix *m) {
    if (!m) return NULL;
    
    Matrix *new_m = matrix_create(m->rows, m->cols);
    if (!new_m) return NULL;
    
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            new_m->data[i][j] = m->data[i][j];
        }
    }
    
    return new_m;
}

void matrix_set(Matrix *m, int row, int col, double value) {
    if (m && row >= 0 && row < m->rows && col >= 0 && col < m->cols) {
        m->data[row][col] = value;
    }
}

double matrix_get(const Matrix *m, int row, int col) {
    if (m && row >= 0 && row < m->rows && col >= 0 && col < m->cols) {
        return m->data[row][col];
    }
    return 0.0;
}

void matrix_print(const Matrix *m) {
    if (!m) return;
    
    for (int i = 0; i < m->rows; i++) {
        printf("[");
        for (int j = 0; j < m->cols; j++) {
            printf("%.2f", m->data[i][j]);
            if (j < m->cols - 1) printf(", ");
        }
        printf("]\n");
    }
}

Matrix* matrix_add(const Matrix *a, const Matrix *b) {
    if (!a || !b || a->rows != b->rows || a->cols != b->cols) return NULL;
    
    Matrix *result = matrix_create(a->rows, a->cols);
    if (!result) return NULL;
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    
    return result;
}

Matrix* matrix_mul(const Matrix *a, const Matrix *b) {
    if (!a || !b || a->cols != b->rows) return NULL;
    
    Matrix *result = matrix_create(a->rows, b->cols);
    if (!result) return NULL;
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < a->cols; k++) {
                sum += a->data[i][k] * b->data[k][j];
            }
            result->data[i][j] = sum;
        }
    }
    
    return result;
}

Matrix* matrix_transpose(const Matrix *m) {
    if (!m) return NULL;
    
    Matrix *result = matrix_create(m->cols, m->rows);
    if (!result) return NULL;
    
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            result->data[j][i] = m->data[i][j];
        }
    }
    
    return result;
}

double matrix_det(const Matrix *m) {
    if (!m || m->rows != m->cols) return 0.0;
    
    int n = m->rows;
    
    if (n == 1) {
        return m->data[0][0];
    } else if (n == 2) {
        return m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
    } else if (n == 3) {
        double a = m->data[0][0], b = m->data[0][1], c = m->data[0][2];
        double d = m->data[1][0], e = m->data[1][1], f = m->data[1][2];
        double g = m->data[2][0], h = m->data[2][1], i = m->data[2][2];
        
        return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    }
    
    return 0.0;
}

Vector* matrix_mul_vector(const Matrix *m, const Vector *v) {
    if (!m || !v || m->cols != v->size) return NULL;
    
    Vector *result = vector_create(m->rows);
    if (!result) return NULL;
    
    for (int i = 0; i < m->rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < m->cols; j++) {
            sum += m->data[i][j] * vector_get(v, j);
        }
        vector_set(result, i, sum);
    }
    
    return result;
}
