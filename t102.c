#include <stdio.h>
#include <stdlib.h>

void task102(int** matrix, int** matrix2, int *A, int *B, int a, int b);
void print_matrix(FILE* out, int** matrix, int rows, int cols);

int main(void) {
  // Объявление переменных
  FILE *in, *out;
  int M, N, rows, cols, x, a, b, dubl;
  int** matrix, **matrix2;
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

  // Выделение памяти под двумерный массив и его копию
  matrix = malloc(rows * sizeof(int*));
  if (!matrix) {
    fprintf(out, "ERROR");
    fclose(out);
    fclose(in);
    return -1;
  }

  matrix2 = malloc(rows * sizeof(int*));
  if (!matrix2) {
    fprintf(out, "ERROR");
    free(matrix);
    fclose(out);
    fclose(in);
    return -1;
  }

  for (int i = 0; i < rows; i++) {
    matrix[i] = malloc(cols * sizeof(int));
    if (!matrix[i]) {
      for (int j = 0; j < i; j++) free(matrix[j]);
      free(matrix);
      free(matrix2);
      fprintf(out, "ERROR");
      fclose(out);
      fclose(in);
      return -1;
    }
  }

  for (int i = 0; i < rows; i++) {
    matrix2[i] = malloc(cols * sizeof(int));
    if (!matrix2[i]) {
      for (int j = 0; j < i; j++) free(matrix2[j]);
      for (int k = 0; k < rows; k++) free(matrix[k]);
      free(matrix);
      free(matrix2);
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
        for (int k = 0; k < rows; k++) {
          free(matrix[k]);
          free(matrix2[k]);
        }
        free(matrix2);
        free(matrix);
        fprintf(out, "ERROR");
        fclose(out);
        fclose(in);
        return -1;
      }
    }
  }

  if (fscanf(in, "%d", &x) != EOF) {
    for (int k = 0; k < rows; k++) {
      free(matrix[k]);
      free(matrix2[k]);
    }
    free(matrix);
    free(matrix2);
    fprintf(out, "ERROR");
    fclose(out);
    fclose(in);
    return -1;
  }

  // Копируем матрицу
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix2[i][j] = matrix[i][j];
    }
  }

  // Выделение памяти под массив индексов строк,
  // относящихся к подмножеству
  A = malloc(rows * sizeof(int));
  if (!A) {
    for (int k = 0; k < rows; k++) {
      free(matrix[k]);
      free(matrix2[k]);
    }
    free(matrix2);
    free(matrix);
    fprintf(out, "ERROR");
    fclose(out);
    fclose(in);
    return -1;
  }

  // Выделение памяти под массив индексов столбцов,
  // относящихся к подмножеству
  B = malloc(cols * sizeof(int));
  if (!B) {
    for (int k = 0; k < rows; k++) {
      free(matrix[k]);
      free(matrix2[k]);
    }
    free(matrix2);
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
      if (M <= matrix[i][j] && matrix[i][j] <= N) {
        A[a] = i;
        a++;
        break;
      }
    }
  }
  b = 0;
  for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
      if (M <= matrix[i][j] && matrix[i][j] <= N) {
        B[b] = j;
        b++;
        break;
      }
    }
  }

  // Решение задачи
  task102(matrix, matrix2, A, B, a, b);  

  // Вывод полученной матрицы в res.txt
  fprintf(out, "%d %d %d %d\n", M, N, rows, cols);
  print_matrix(out, matrix2, rows, cols);

  // Освобождение памяти и закрытие файлов
  for (int k = 0; k < rows; k++) {
    free(matrix[k]);
    free(matrix2[k]);
  }
  free(matrix2);
  free(matrix);
  free(A);
  free(B);
  fclose(out);
  fclose(in);
  return 0;
}

// Функция решения задачи
void task102(int** matrix, int** matrix2, int *A, int *B, int a, int b) {
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < b; j++) {
      int count = 0;
      int target = matrix[A[i]][B[j]];
      for (int k = 0; k < a; k++) {
        if (matrix[A[k]][B[j]] == target) {
          count++;
        }
      }
      if (count >= 2) {
        for (int k = 0; k < a; k++) {
          if (matrix[A[k]][B[j]] == target) {
            matrix2[A[k]][B[j]] = 1;
          }
        }
      } else {
        matrix2[A[i]][B[j]] = 0;
      }
    }
  }
}

void print_matrix(FILE* out, int** matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      fprintf(out, "%d", matrix[i][j]);
      if (j < cols - 1) {
        fprintf(out, " ");
      }
    }
    if (i < rows - 1) {
     fprintf(out, "\n");
    }
  }
}
