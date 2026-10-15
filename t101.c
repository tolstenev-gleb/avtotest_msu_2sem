#include <stdio.h>
#include <stdlib.h>

void task101(int** matrix, int *A, int *B, int a, int b);
void print_matrix(FILE* out, int** matrix, int rows, int cols);

int main(void) {
  // Объявление переменных
  FILE *in, *out;
  int M, N, rows, cols, x, a, b, dubl;
  int** matrix;
  int *A, *B;

  // Открытие файла res.txt
  out = fopen("res.txt", "w");
  if (!out) return -1;

  // Открытие файла data.txt
  in = fopen("data.txt", "r");
  if (!in) {
    fprintf(out, "ERROR");
    fclose(out);
    return -1;
  }

  // Считываем числа M, N, rows, cols
  if (fscanf(in, "%d %d %d %d", &M, &N, &rows, &cols) != 4) {
    fprintf(out, "ERROR");
    fclose(out);
    fclose(in);
    return -1;
  }

  // Выделение памяти под двумерный массив
  matrix = malloc(rows * sizeof(int*));
  if (!matrix) {
    fprintf(out, "ERROR");
    fclose(out);
    fclose(in);
    return -1;
  }

  for (int i = 0; i < rows; i++) {
    matrix[i] = malloc(cols * sizeof(int));
    if (!matrix[i]) {
      for (int j = 0; j < i; j++) free(matrix[j]);
      free(matrix);
      fprintf(out, "ERROR");
      fclose(out);
      fclose(in);
      return -1;
    }
  }

  // Заполняем матрицу из файла
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (fscanf(in, "%d", &matrix[i][j]) != 1) {
        for (int k = 0; k < rows; k++) free(matrix[k]);
        free(matrix);
        fprintf(out, "ERROR");
        fclose(out);
        fclose(in);
        return -1;
      }
    }
  }

  if (fscanf(in, "%d", &x) != EOF) {
    for (int k = 0; k < rows; k++) free(matrix[k]);
    free(matrix);
    fprintf(out, "ERROR");
    fclose(out);
    fclose(in);
    return -1;
  }
  A = malloc(rows * sizeof(int));
  if (!A) {
    for (int k = 0; k < rows; k++) free(matrix[k]);
    free(matrix);
    fprintf(out, "ERROR");
    fclose(out);
    fclose(in);
    return -1;
  }
  B = malloc(cols * sizeof(int));
  if (!B) {
    for (int k = 0; k < rows; k++) free(matrix[k]);
    free(matrix);
    free(A);
    fprintf(out, "ERROR");
    fclose(out);
    fclose(in);
    return -1;
  }
  a = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (matrix[i][j] % M == N) {
        A[a] = i;
        a++;
        break;
      }
    }
  }
  b = 0;
  for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
      if (matrix[i][j] % M == N) {
        B[b] = j;
        b++;
        break;
      }
    }
  }

  // Решение задачи
  task101(matrix, A, B, a, b);

  // Вывод полученной матрицы в res.txt
  fprintf(out, "%d %d %d %d\n", M, N, rows, cols);
  print_matrix(out, matrix, rows, cols);

  // Освобождение памяти и закрытие файлов
  for (int k = 0; k < rows; k++) free(matrix[k]);
  free(matrix);
  free(A);
  free(B);
  fclose(out);
  fclose(in);
  return 0;
}

// Функция решения задачи
void task101(int** matrix, int *A, int *B, int a, int b) {
  for (int i = a - 1; i >= 0; i--) {
    for (int j = b - 1; j >= 0; j--) {
      int dubl = 0;
      for (int k = 0; k < j; k++) {
        if (matrix[A[i]][B[j]] == matrix[A[i]][B[k]]) {
          dubl = 1;
          break;
        }
      }
      if (dubl == 1) {
        matrix[A[i]][B[j]] = 1;
      } else {
        matrix[A[i]][B[j]] = 0;
      }
    }
  }
}

void print_matrix(FILE* out, int** matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      fprintf(out, "%d ", matrix[i][j]);
    }
    fprintf(out, "\n");
  }
}
