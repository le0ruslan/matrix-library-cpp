#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int returnable = OK;
  if (rows > 0 && columns > 0) {
    result->matrix = calloc((size_t)rows, sizeof(double *));
    if (result->matrix != NULL) {
      result->columns = columns;
      result->rows = rows;
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc((size_t)columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          s21_remove_matrix(result);
          returnable = INCORRECT;
          break;
        }
      }
    } else {
      returnable = INCORRECT;
    }
  } else {
    result->matrix = NULL;
    returnable = INCORRECT;
  }
  return returnable;
}

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!A || !B || A->rows != B->rows || A->columns != B->columns) {
    return FAILURE;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      double diff = A->matrix[i][j] - B->matrix[i][j];
      if (fabs(diff) > PRECISION) {
        return FAILURE;
      }
    }
  }
  return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = OK;
  if (A != NULL && B != NULL) {
    if (A->rows != B->rows || A->columns != B->columns) {
      error_code = ERR;
    } else {
      error_code = s21_create_matrix(A->rows, A->columns, result);
      if (error_code == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  } else {
    error_code = INCORRECT;
  }
  return error_code;
}
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = OK;
  if (A != NULL && B != NULL) {
    if (A->rows != B->rows || A->columns != B->columns) {
      error_code = ERR;
    } else {
      error_code = s21_create_matrix(A->rows, A->columns, result);
      if (error_code == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  } else {
    error_code = INCORRECT;
  }
  return error_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int returnable = OK;
  if (A->matrix != NULL) {
    returnable = s21_create_matrix(A->rows, A->columns, result);
    if (returnable == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    returnable = INCORRECT;
  }
  return returnable;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int returnable = OK;
  if (s21_check_matrix(A) == OK && s21_check_matrix(B) == OK) {
    if (A->columns == B->rows) {
      int returnable = s21_create_matrix(A->rows, B->columns, result);
      if (returnable == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            for (int k = 0; k < A->columns; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    } else {
      returnable = ERR;
    }
  } else {
    returnable = INCORRECT;
  }
  return returnable;
}

int s21_check_matrix(matrix_t *A) {
  int error_code = OK;
  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1) {
    error_code = ERR;
  }
  return error_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int returnable = s21_check_matrix(A);
  if (returnable == OK) {
    returnable = s21_create_matrix(A->columns, A->rows, result);
    if (returnable == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return returnable;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int returnable = s21_check_matrix(A);
  if (returnable == OK) {
    if (A->rows == A->columns) {
      returnable = s21_create_matrix(A->rows, A->columns, result);
      if (returnable == OK) {
        if (A->rows == 1) {
          result->matrix[0][0] = A->matrix[0][0];
        } else if (A->rows == 2) {
          matrix_t forMinor;
          s21_create_matrix(1, 1, &forMinor);
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
              s21_minor_matrix(i, j, A, &forMinor);
              result->matrix[i][j] = forMinor.matrix[0][0] * pow(-1, (i + j));
            }
          }
          s21_remove_matrix(&forMinor);
        } else {
          matrix_t forMinor;
          s21_create_matrix((A->rows) - 1, (A->columns) - 1, &forMinor);
          double res = 0;
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
              s21_minor_matrix(i, j, A, &forMinor);
              s21_determinant(&forMinor, &res);
              result->matrix[i][j] = res * pow(-1, (i + j));
              res = 0;
            }
          }
          s21_remove_matrix(&forMinor);
        }
      }
    } else {
      returnable = ERR;
      result->matrix = NULL;
      result->rows = 0;
      result->columns = 0;
    }
  }
  return returnable;
}

int s21_zero_det_check(matrix_t *A) {
  int zero_column_counter = 0;
  int zero_row_counter = 0;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (A->matrix[j][i] == 0) {
        zero_column_counter++;
      }

      if (A->matrix[i][j] == 0) {
        zero_row_counter++;
      }
    }

    if (zero_column_counter == A->rows || zero_row_counter == A->columns) {
      break;
    } else {
      zero_column_counter = 0;
      zero_row_counter = 0;
    }
  }

  return (zero_column_counter == A->rows || zero_row_counter == A->columns);
}

void s21_minor_matrix(int I, int J, matrix_t *A, matrix_t *result) {
  int resI = 0;
  int resJ = 0;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i != I && j != J) {
        result->matrix[resI][resJ] = A->matrix[i][j];

        if (resJ < (result->columns) - 1) {
          resJ++;
        } else {
          resJ = 0;
          resI++;
        }
      }
    }
  }
}

int s21_zero_cnt(matrix_t *A) {
  int zero_count = 0;

  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i][i] == 0) {
      zero_count++;
    }
  }

  return zero_count;
}

int s21_determinant(matrix_t *A, double *result) {
  int returnable = s21_check_matrix(A);

  if (returnable == OK) {
    if (A->columns == A->rows) {
      if (A->rows == 1) {
        *(result) = A->matrix[0][0];
      } else if (A->rows == 2) {
        *(result) = (A->matrix[0][0] * A->matrix[1][1]) -
                    (A->matrix[0][1] * A->matrix[1][0]);
      } else if (A->rows >= 3) {
        if (s21_zero_det_check(A) == 1) {
          *(result) = 0;
        } else {
          int swap_cnt = 0;
          while (s21_zero_cnt(A) != 0) s21_swap_matrix(A, &swap_cnt);
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
              if (i > j) {
                if (fabs(A->matrix[i][j] - 0.000000) > PRECISION) {
                  double coef = 0.0;
                  if (j == 0) {
                    coef = (A->matrix[i][0] / A->matrix[0][0]) * (-1);
                    for (int elem = 0; elem < A->columns; elem++) {
                      A->matrix[i][elem] += (A->matrix[0][elem] * coef);
                    }
                  } else {
                    coef = (A->matrix[i][j] / A->matrix[i - 1][j]) * (-1);
                    for (int elem = j; elem < A->columns; elem++) {
                      A->matrix[i][elem] += (A->matrix[i - 1][elem] * coef);
                    }
                  }
                }
              }
            }
          }
          *(result) = 1;
          for (int a = 0; a < A->rows; a++) {
            for (int b = 0; b < A->columns; b++) {
              if (a == b) {
                *(result) *= A->matrix[a][b];
              }
            }
          }
          if (swap_cnt % 2 != 0) {
            *(result) *= (-1);
          }
        }
      }
    } else {
      returnable = ERR;
    }
  }
  return returnable;
}

int s21_swap_matrix(matrix_t *A, int *swap_cnt) {
  double *buffer = calloc(A->columns, sizeof(double));
  int row_to_swap = 0;

  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i][i] == 0) {
      row_to_swap = s21_find_row_to_swap(A);

      for (int j = 0; j < A->columns; j++) {
        buffer[j] = A->matrix[row_to_swap][j];
        A->matrix[row_to_swap][j] = A->matrix[i][j];
        A->matrix[i][j] = buffer[j];
      }

      (*swap_cnt)++;
    }
  }

  free(buffer);

  return *swap_cnt;
}

int s21_find_row_to_swap(matrix_t *A) {
  int no_s21_zero_cnt = 0;
  int i = 0;

  for (; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (A->matrix[i][j] != 0) {
        no_s21_zero_cnt++;
      }
    }

    if (no_s21_zero_cnt == A->columns) {
      break;
    } else {
      no_s21_zero_cnt = 0;
    }
  }

  return i;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int returnable = s21_check_matrix(A);
  if (returnable == OK) {
    if (A->columns == A->rows) {
      double res = 0;
      matrix_t A_copy;

      s21_create_matrix(A->rows, A->columns, &A_copy);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          A_copy.matrix[i][j] = A->matrix[i][j];
        }
      }

      s21_determinant(&A_copy, &res);

      if (fabs(res - 0.000000) > PRECISION) {
        matrix_t transpose;
        s21_transpose(A, &transpose);
        s21_calc_complements(&transpose, result);
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] *= (1 / res);
          }
        }
        s21_remove_matrix(&transpose);
        s21_remove_matrix(&A_copy);
      } else {
        s21_remove_matrix(&A_copy);
        returnable = ERR;
      }
    } else {
      returnable = ERR;
    }
  }
  return returnable;
}