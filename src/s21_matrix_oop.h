#include <cmath>
#include <iostream>

#define FOR_EQ 1
#define FOR_MUL_MAT 2
#define FOR_DTR 3

class S21Matrix {
  int _rows, _cols;
  double **_mat;
  void allocMem();
  void freeMem();
  bool trueVal(S21Matrix other, int var);
  double mulLogic(S21Matrix other, int r, int c);
  double dtrTwoTwo();
  double dtrThreeThree();
  S21Matrix cutMatrix(int notR, int notC);

 public:
  //  Конструкторы и деструкторы
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();
  // Перегрузка операторов
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double num) const;
  friend S21Matrix operator*(double, S21Matrix &mat);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  double &operator()(int row, int col);
  double &operator()(int row, int col) const;

  int Get_rows() const;
  int Get_cols() const;
  // double* Get_mat() const;
  void Set_rows(int value_cols);
  void Set_cols(int value_rows);

  friend void T_numirateTestMat(S21Matrix *mat, int num, int umnum);
  friend void T_printTestMat(const S21Matrix &mat);
  friend void T_printValMat(const S21Matrix &mat);
  friend void T_print(const S21Matrix &mat);
  friend void T_set_mat(S21Matrix *mat, int r, int c, double num);

  // Операции над матрицами
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
};
