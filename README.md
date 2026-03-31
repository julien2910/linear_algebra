# Linear Algebra Library

Библиотека для работы с векторами и матрицами на языке C.

## Функции

### Векторы (10 функций)
- `vector_create` - создание вектора
- `vector_free` - освобождение памяти
- `vector_set` - установка элемента
- `vector_get` - получение элемента
- `vector_print` - вывод вектора
- `vector_add` - сложение векторов
- `vector_sub` - вычитание векторов
- `vector_mul_scalar` - умножение на скаляр
- `vector_dot` - скалярное произведение
- `vector_norm` - норма вектора

### Матрицы (8 функций)
- `matrix_create` - создание матрицы
- `matrix_free` - освобождение памяти
- `matrix_set/get` - доступ к элементам
- `matrix_add` - сложение матриц
- `matrix_mul` - умножение матриц
- `matrix_transpose` - транспонирование
- `matrix_det` - определитель (2x2, 3x3)
- `matrix_mul_vector` - умножение матрицы на вектор
