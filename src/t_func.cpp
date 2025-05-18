#include "s21_matrix_oop.h"

void T_printValMat(const S21Matrix& mat) {
  std::cout << "_rows = " << mat._rows << "\n_cols = " << mat._cols
            << std::endl;
}

void T_print(const S21Matrix& mat) {
  T_printTestMat(mat);
  T_printValMat(mat);
}

void T_printTestMat(const S21Matrix& mat) {
  for (int r = 0; r < mat._rows; r++) {
    for (int c = 0; c < mat._cols; c++) {
      if (mat._mat[r][c] < 10)
        std::cout << " " << " " << mat._mat[r][c] << "|";
      else if (mat._mat[r][c] < 100)
        std::cout << " " << mat._mat[r][c] << "|";
      else
        std::cout << mat._mat[r][c] << "|";
    }
    std::cout << std::endl;
  }
}

void T_numirateTestMat(S21Matrix* mat, int num, int ni) {
  int umnum = 1;
  for (int r = 0; r < mat->_rows; r++) {
    for (int c = 0; c < mat->_cols; c++) {
      for (int g = 0; g < ni; g++, umnum++) mat->_mat[r][c] = num + umnum;
    }
  }
}

void T_set_mat(S21Matrix* mat, int r, int c, double num) {
  while (1) {
    mat->_mat[r][c] = num;
    break;
  }
}

int main() {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 0.0;
  A(1, 1) = 1.0;
  A(1, 2) = 4.0;
  A(2, 0) = 5.0;
  A(2, 1) = 6.0;
  A(2, 2) = 0.0;

  S21Matrix B(3, 3);
  B(0, 0) = -24.0;
  B(0, 1) = 20.0;
  B(0, 2) = -5.0;

  B(1, 0) = 18.0;
  B(1, 1) = -15.0;
  B(1, 2) = 4.0;

  B(2, 0) = 5.0;
  B(2, 1) = -4.0;
  B(2, 2) = 1.0;

  S21Matrix C = A.CalcComplements();
  T_print(C);
  return 0;
}
