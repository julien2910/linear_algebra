#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    double **data;
    int rows;
    int cols;
} Matrix;

// Создание и уничтожение
Matrix* matrix_create(int rows, int cols);
void matrix_free(Matrix *m);
Matrix* matrix_copy(const Matrix *m);

// Доступ к элементам
void matrix_set(Matrix *m, int row, int col, double value);
double matrix_get(const Matrix *m, int row, int col);
void matrix_print(const Matrix *m);

// Операции с матрицами
Matrix* matrix_add(const Matrix *a, const Matrix *b);
Matrix* matrix_mul(const Matrix *a, const Matrix *b);
Matrix* matrix_transpose(const Matrix *m);
double matrix_det(const Matrix *m); // только для квадратных матриц 2x2 и 3x3

// Векторно-матричные операции
Vector* matrix_mul_vector(const Matrix *m, const Vector *v);

#endif
