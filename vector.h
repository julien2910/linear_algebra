#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    double *data;
    int size;
} Vector;

// Создание и уничтожение
Vector* vector_create(int size);
void vector_free(Vector *v);
Vector* vector_copy(const Vector *v);

// Базовые операции
void vector_set(Vector *v, int index, double value);
double vector_get(const Vector *v, int index);
void vector_print(const Vector *v);

// Арифметические операции
Vector* vector_add(const Vector *a, const Vector *b);
Vector* vector_sub(const Vector *a, const Vector *b);
Vector* vector_mul_scalar(const Vector *v, double scalar);
double vector_dot(const Vector *a, const Vector *b);
double vector_norm(const Vector *v);
Vector* vector_normalize(const Vector *v);

#endif
