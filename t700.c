#include <stdio.h>
#include <stdlib.h>

int task700 (int **matrix, int rows, int *a, int k);
int correct_col(int **matrix, int rows, int j, int M);
int min_elem(int **matrix, int rows, int j);
void swap_cols(int **matrix, int rows, int a, int b);
int max_elem_in_col(int **matrix, int rows, int j);
void print_matrix(FILE *out, int **matrix, int rows, int cols);

int main(void) {
    FILE *in, *out;
    int M, rows, cols, x;
    int **matrix;
    int *a, k = 0;

    out = fopen("res.txt", "w");
    if (!out) return -1;

    in = fopen("data.txt", "r");
    if (!in) {
        fprintf(out, "ERROR");
        fclose(out);
        return -1;
    }

    if (fscanf(in, "%d %d %d", &M, &rows, &cols) != 3) {
        fprintf(out, "ERROR");
        fclose(out);
        fclose(in);
        return -1;
    }

    // Содержит индексы подмножества
    a = malloc(cols * sizeof(int));
    if (!a) {
        fprintf(out, "ERROR");
        fclose(out);
        fclose(in);
        return -1;
    }

    matrix = malloc(rows * sizeof(int *));
    if (!matrix) {
        fprintf(out, "ERROR");
        free(a);
        fclose(out);
        fclose(in);
        return -1;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            free(a);
            fprintf(out, "ERROR");
            fclose(out);
            fclose(in);
            return -1;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(in, "%d", &matrix[i][j]) != 1) {
                for (int k = 0; k < rows; k++) free(matrix[k]);
                free(matrix);
                free(a);
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
        free(a);
        fprintf(out, "ERROR");
        fclose(out);
        fclose(in);
        return -1;
    }

    for (int j = 0; j < cols; j++) {
        if (correct_col(matrix, rows, j, M)) {
            a[k] = j;
            k++;
        }
    }

    x = task700(matrix, rows, a, k);
    if (x == -1) {
        fprintf(out, "ERROR");
    } else {
        fprintf(out, "%d %d %d\n", M, rows, cols);
        print_matrix(out, matrix, rows, cols);
    }

    for (int k = 0; k < rows; k++) free(matrix[k]);
    free(matrix);
    free(a);
    fclose(out);
    fclose(in);
    return 0;
}

void print_array(int *array, int size) {
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void print_debug(int *a, int* min, int k, int** matrix) {
    printf("  a: ");
    print_array(a, k);
    printf("min: ");
    print_array(min, k);
    print_matrix(stdout, matrix, 3, 7);
    printf("\n");
    printf("\n");
}

int task700 (int **matrix, int rows, int *a, int k) {
  int *min = malloc(k * sizeof(int));
  if (!min) {
    return -1;
  }
  for (int j = 0; j < k; j++) {
    min[j] = min_elem(matrix, rows, a[j]);
  }
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < k; j++) {
        if (min[i] > min[j]) {
            
            int tmp;
            swap_cols(matrix, rows, a[i], a[j]);
            tmp = min[i];
            min[i] = min[j];
            min[j] = tmp;

        }
    }
  }
  free(min);
  return 0;
}



int correct_col(int **matrix, int rows, int j, int M) {
    int c = 0;
    for (int i = 0; i < rows; i++) {
        if (matrix[i][j] % M == 0) {
            c++;
        }
    }
    if (c == rows) {
        return 1; 
    } else {
        return 0;
    }
}

int min_elem(int **matrix, int rows, int j) {
    int min = matrix[0][j];
    for (int i = 0; i < rows; i++)
    {
        if (matrix[i][j] < min)
        {
            min = matrix[i][j];
        }
    }
    return min;
}

void swap_cols(int **matrix, int rows, int a, int b) {
    for (int i = 0; i < rows; i++) {
        int tmp = matrix[i][a];
        matrix[i][a] = matrix[i][b];
        matrix[i][b] = tmp;
    }
}

void print_matrix(FILE *out, int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(out, "%2d ", matrix[i][j]);
        }
        if (i != rows - 1) {
            fprintf(out, "\n");
        }
    }
}
