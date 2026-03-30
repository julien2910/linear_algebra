#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "vector.h"
#include "matrix.h"

#define EPS 1e-9

void test_vector_operations() {
    printf("Testing vector operations...\n");
    
    Vector *v1 = vector_create(3);
    Vector *v2 = vector_create(3);
    
    vector_set(v1, 0, 1.0);
    vector_set(v1, 1, 2.0);
    vector_set(v1, 2, 3.0);
    
    vector_set(v2, 0, 4.0);
    vector_set(v2, 1, 5.0);
    vector_set(v2, 2, 6.0);
    
    // Test addition
    Vector *sum = vector_add(v1, v2);
    assert(fabs(vector_get(sum, 0) - 5.0) < EPS);
    assert(fabs(vector_get(sum, 1) - 7.0) < EPS);
    assert(fabs(vector_get(sum, 2) - 9.0) < EPS);
    vector_free(sum);
    
    // Test subtraction
    Vector *diff = vector_sub(v1, v2);
    assert(fabs(vector_get(diff, 0) - (-3.0)) < EPS);
    assert(fabs(vector_get(diff, 1) - (-3.0)) < EPS);
    assert(fabs(vector_get(diff, 2) - (-3.0)) < EPS);
    vector_free(diff);
    
    // Test scalar multiplication
    Vector *scaled = vector_mul_scalar(v1, 2.0);
    assert(fabs(vector_get(scaled, 0) - 2.0) < EPS);
    assert(fabs(vector_get(scaled, 1) - 4.0) < EPS);
    assert(fabs(vector_get(scaled, 2) - 6.0) < EPS);
    vector_free(scaled);
    
    // Test dot product
    double dot = vector_dot(v1, v2);
    assert(fabs(dot - 32.0) < EPS);
    
    // Test norm
    double norm = vector_norm(v1);
    assert(fabs(norm - sqrt(14.0)) < EPS);
    
    // Test normalization
    Vector *normalized = vector_normalize(v1);
    assert(fabs(vector_norm(normalized) - 1.0) < EPS);
    vector_free(normalized);
    
    vector_free(v1);
    vector_free(v2);
    
    printf("Vector tests passed!\n");
}

void test_matrix_operations() {
    printf("Testing matrix operations...\n");
    
    Matrix *m1 = matrix_create(2, 3);
    Matrix *m2 = matrix_create(3, 2);
    
    // Fill matrices
    matrix_set(m1, 0, 0, 1.0); matrix_set(m1, 0, 1, 2.0); matrix_set(m1, 0, 2, 3.0);
    matrix_set(m1, 1, 0, 4.0); matrix_set(m1, 1, 1, 5.0); matrix_set(m1, 1, 2, 6.0);
    
    matrix_set(m2, 0, 0, 7.0); matrix_set(m2, 0, 1, 8.0);
    matrix_set(m2, 1, 0, 9.0); matrix_set(m2, 1, 1, 10.0);
    matrix_set(m2, 2, 0, 11.0); matrix_set(m2, 2, 1, 12.0);
    
    // Test matrix multiplication
    Matrix *product = matrix_mul(m1, m2);
    assert(fabs(matrix_get(product, 0, 0) - 58.0) < EPS);
    assert(fabs(matrix_get(product, 0, 1) - 64.0) < EPS);
    assert(fabs(matrix_get(product, 1, 0) - 139.0) < EPS);
    assert(fabs(matrix_get(product, 1, 1) - 154.0) < EPS);
    matrix_free(product);
    
    // Test transpose
    Matrix *transpose = matrix_transpose(m1);
    assert(transpose->rows == 3 && transpose->cols == 2);
    assert(fabs(matrix_get(transpose, 0, 0) - 1.0) < EPS);
    assert(fabs(matrix_get(transpose, 1, 0) - 2.0) < EPS);
    assert(fabs(matrix_get(transpose, 2, 0) - 3.0) < EPS);
    matrix_free(transpose);
    
    matrix_free(m1);
    matrix_free(m2);
    
    printf("Matrix tests passed!\n");
}

void test_matrix_determinant() {
    printf("Testing determinant...\n");
    
    // Test 2x2 matrix
    Matrix *m2 = matrix_create(2, 2);
    matrix_set(m2, 0, 0, 1.0); matrix_set(m2, 0, 1, 2.0);
    matrix_set(m2, 1, 0, 3.0); matrix_set(m2, 1, 1, 4.0);
    assert(fabs(matrix_det(m2) - (-2.0)) < EPS);
    matrix_free(m2);
    
    // Test 3x3 matrix
    Matrix *m3 = matrix_create(3, 3);
    matrix_set(m3, 0, 0, 1.0); matrix_set(m3, 0, 1, 2.0); matrix_set(m3, 0, 2, 3.0);
    matrix_set(m3, 1, 0, 4.0); matrix_set(m3, 1, 1, 5.0); matrix_set(m3, 1, 2, 6.0);
    matrix_set(m3, 2, 0, 7.0); matrix_set(m3, 2, 1, 8.0); matrix_set(m3, 2, 2, 9.0);
    assert(fabs(matrix_det(m3)) < EPS);
    matrix_free(m3);
    
    printf("Determinant tests passed!\n");
}

void test_matrix_vector_multiplication() {
    printf("Testing matrix-vector multiplication...\n");
    
    Matrix *m = matrix_create(2, 2);
    matrix_set(m, 0, 0, 1.0); matrix_set(m, 0, 1, 2.0);
    matrix_set(m, 1, 0, 3.0); matrix_set(m, 1, 1, 4.0);
    
    Vector *v = vector_create(2);
    vector_set(v, 0, 5.0);
    vector_set(v, 1, 6.0);
    
    Vector *result = matrix_mul_vector(m, v);
    assert(fabs(vector_get(result, 0) - 17.0) < EPS);
    assert(fabs(vector_get(result, 1) - 39.0) < EPS);
    
    vector_free(v);
    vector_free(result);
    matrix_free(m);
    
    printf("Matrix-vector multiplication tests passed!\n");
}

void test_memory_management() {
    printf("Testing memory management...\n");
    
    // Test vector copy
    Vector *v1 = vector_create(3);
    vector_set(v1, 0, 1.0);
    vector_set(v1, 1, 2.0);
    vector_set(v1, 2, 3.0);
    
    Vector *v2 = vector_copy(v1);
    assert(v2 != NULL);
    assert(v2->size == v1->size);
    assert(fabs(vector_get(v2, 0) - 1.0) < EPS);
    
    vector_free(v1);
    vector_free(v2);
    
    // Test matrix copy
    Matrix *m1 = matrix_create(2, 2);
    matrix_set(m1, 0, 0, 1.0);
    matrix_set(m1, 0, 1, 2.0);
    matrix_set(m1, 1, 0, 3.0);
    matrix_set(m1, 1, 1, 4.0);
    
    Matrix *m2 = matrix_copy(m1);
    assert(m2 != NULL);
    assert(m2->rows == m1->rows);
    assert(m2->cols == m1->cols);
    assert(fabs(matrix_get(m2, 0, 0) - 1.0) < EPS);
    
    matrix_free(m1);
    matrix_free(m2);
    
    printf("Memory management tests passed!\n");
}

int main() {
    printf("====================================\n");
    printf("Linear Algebra Library Tests\n");
    printf("====================================\n\n");
    
    test_vector_operations();
    test_matrix_operations();
    test_matrix_determinant();
    test_matrix_vector_multiplication();
    test_memory_management();
    
    printf("\n====================================\n");
    printf("All tests passed successfully!\n");
    printf("====================================\n");
    
    return 0;
}
