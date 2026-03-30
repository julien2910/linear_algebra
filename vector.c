#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Vector* vector_create(int size) {
    if (size <= 0) return NULL;
    
    Vector *v = (Vector*)malloc(sizeof(Vector));
    if (!v) return NULL;
    
    v->data = (double*)calloc(size, sizeof(double));
    if (!v->data) {
        free(v);
        return NULL;
    }
    
    v->size = size;
    return v;
}

void vector_free(Vector *v) {
    if (v) {
        free(v->data);
        free(v);
    }
}

Vector* vector_copy(const Vector *v) {
    if (!v) return NULL;
    
    Vector *new_v = vector_create(v->size);
    if (!new_v) return NULL;
    
    for (int i = 0; i < v->size; i++) {
        new_v->data[i] = v->data[i];
    }
    
    return new_v;
}

void vector_set(Vector *v, int index, double value) {
    if (v && index >= 0 && index < v->size) {
        v->data[index] = value;
    }
}

double vector_get(const Vector *v, int index) {
    if (v && index >= 0 && index < v->size) {
        return v->data[index];
    }
    return 0.0;
}

void vector_print(const Vector *v) {
    if (!v) return;
    
    printf("[");
    for (int i = 0; i < v->size; i++) {
        printf("%.2f", v->data[i]);
        if (i < v->size - 1) printf(", ");
    }
    printf("]\n");
}

Vector* vector_add(const Vector *a, const Vector *b) {
    if (!a || !b || a->size != b->size) return NULL;
    
    Vector *result = vector_create(a->size);
    if (!result) return NULL;
    
    for (int i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] + b->data[i];
    }
    
    return result;
}

Vector* vector_sub(const Vector *a, const Vector *b) {
    if (!a || !b || a->size != b->size) return NULL;
    
    Vector *result = vector_create(a->size);
    if (!result) return NULL;
    
    for (int i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] - b->data[i];
    }
    
    return result;
}

Vector* vector_mul_scalar(const Vector *v, double scalar) {
    if (!v) return NULL;
    
    Vector *result = vector_create(v->size);
    if (!result) return NULL;
    
    for (int i = 0; i < v->size; i++) {
        result->data[i] = v->data[i] * scalar;
    }
    
    return result;
}

double vector_dot(const Vector *a, const Vector *b) {
    if (!a || !b || a->size != b->size) return 0.0;
    
    double sum = 0.0;
    for (int i = 0; i < a->size; i++) {
        sum += a->data[i] * b->data[i];
    }
    
    return sum;
}

double vector_norm(const Vector *v) {
    if (!v) return 0.0;
    
    double sum = 0.0;
    for (int i = 0; i < v->size; i++) {
        sum += v->data[i] * v->data[i];
    }
    
    return sqrt(sum);
}

Vector* vector_normalize(const Vector *v) {
    if (!v) return NULL;
    
    double norm = vector_norm(v);
    if (norm < 1e-10) return NULL;
    
    return vector_mul_scalar(v, 1.0 / norm);
}
