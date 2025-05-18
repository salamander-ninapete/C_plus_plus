#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : _rows(3), _cols(3) { S21Matrix::allocMem(); }

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  if (rows <= 0 || cols <= 0)
    throw std::invalid_argument(
        "Rows or columns can`t be less than or equal to zero");
  S21Matrix::allocMem();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : _rows(other._rows), _cols(other._cols) {
  allocMem();
  for (int r = 0; r < _rows; r++) {
    for (int c = 0; c < _cols; c++) {
      _mat[r][c] = other._mat[r][c];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : _rows(other._rows), _cols(other._cols), _mat(other._mat) {
  other._rows = 0;
  other._cols = 0;
  other._mat = nullptr;
}

S21Matrix::~S21Matrix() {
  if (_mat) {
    freeMem();
  }
  _mat = nullptr;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    freeMem();
    _rows = other._rows;
    _cols = other._cols;
    _mat = other._mat;

    other._rows = 0;
    other._cols = 0;
    other._mat = nullptr;
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix newMat(*this);
  newMat.SumMatrix(other);
  return newMat;
}
S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix newMat(*this);
  newMat.SubMatrix(other);
  return newMat;
}
S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix newMat(*this);
  newMat.MulMatrix(other);
  return newMat;
}
S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix newMat(*this);
  newMat.MulNumber(num);
  return newMat;
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= _rows || col >= _cols) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  return _mat[row][col];
}

double &S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= _rows || col >= _cols) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  return _mat[row][col];
}
S21Matrix operator*(double num, S21Matrix mat) { return mat * num; }
bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    freeMem();
    _rows = other._rows;
    _cols = other._cols;
    allocMem();
    for (int r = 0; r < _rows; r++) {
      for (int c = 0; c < _cols; c++) {
        _mat[r][c] = other._mat[r][c];
      }
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

void S21Matrix::allocMem() {
  _mat = new double *[_rows]();
  for (int r = 0; r < _rows; r++) {
    _mat[r] = new double[_cols]();
  }
}

void S21Matrix::freeMem() {
  for (int r = 0; r < _rows; r++) {
    delete[] _mat[r];
  }
  delete[] _mat;
}

int S21Matrix::Get_cols() const { return _cols; }
int S21Matrix::Get_rows() const { return _rows; }
// double *S21Matrix::Get_mat() const { return *_mat; }

void S21Matrix::Set_cols(int cols) {
  if (cols <= 0)
    throw std::invalid_argument("Columns can`t be less than or equal to zero");
  S21Matrix newMat(_rows, cols);
  int min_cols = cols < _cols ? cols : _cols;
  for (int r = 0; r < _rows; r++) {
    for (int c = 0; c < min_cols; c++) {
      newMat._mat[r][c] = this->_mat[r][c];
    }
  }
  *this = newMat;
}

void S21Matrix::Set_rows(int rows) {
  if (rows <= 0)
    throw std::invalid_argument("Rows can`t be less than or equal to zero");
  S21Matrix newMat(rows, _cols);
  int min_rows = rows < _rows ? rows : _rows;
  for (int r = 0; r < min_rows; r++) {
    for (int c = 0; c < _cols; c++) {
      newMat._mat[r][c] = this->_mat[r][c];
    }
  }
  *this = newMat;
}

bool S21Matrix::trueVal(S21Matrix other, int var) {
  bool answer = false;
  if (var == FOR_EQ) {
    if ((Get_rows() == other.Get_rows()) && (Get_cols() == other.Get_cols()))
      answer = true;
  } else if (var == FOR_MUL_MAT) {
    if (Get_cols() == other.Get_rows()) answer = true;
  } else if (var == FOR_DTR) {
    if (other.Get_cols() == other.Get_rows()) answer = true;
  }
  return answer;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool answer = true;
  if (!trueVal(other, FOR_EQ))
    answer = false;
  else {
    for (int r = 0; r < other.Get_rows(); r++) {
      for (int c = 0; c < other.Get_cols(); c++) {
        if (((_mat[r][c] - other._mat[r][c]) > 1e-7)) answer = false;
      }
    }
  }
  return answer;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!trueVal(other, FOR_EQ))
    throw std::range_error(
        "number of columns and rows are not equal \n if r1 == r2 && c1 == c2 "
        "-> (r1 X c1) + (r2 X c2)  ");
  for (int r = 0; r < other.Get_rows(); r++) {
    for (int c = 0; c < other.Get_cols(); c++) {
      _mat[r][c] += other._mat[r][c];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!trueVal(other, FOR_EQ))
    throw std::range_error(
        "number of columns and rows are not equal\n if r1 == r2 && c1 == c2 -> "
        "(r1 X c1) - (r2 X c2) ");
  for (int r = 0; r < other.Get_rows(); r++) {
    for (int c = 0; c < other.Get_cols(); c++) {
      _mat[r][c] -= other._mat[r][c];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int r = 0; r < Get_rows(); r++) {
    for (int c = 0; c < Get_cols(); c++) {
      _mat[r][c] *= num;
    }
  }
}

double S21Matrix::mulLogic(S21Matrix other, int r, int c) {
  double result = 0;
  for (int c1 = 0, r2 = 0; r2 < other._rows; c1++, r2++) {
    result += _mat[r][c1] * other._mat[r2][c];
  }
  return result;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (!trueVal(other, FOR_MUL_MAT))
    throw std::out_of_range(
        "the number of columns of the first and rows of the second is not "
        "equal\n if c1 == r2 -> (r1 X c1) * (r2 X c2)");
  S21Matrix result(_rows, other._cols);
  for (int r = 0; r < result.Get_rows(); r++) {
    for (int c = 0; c < result.Get_cols(); c++) {
      result._mat[r][c] = mulLogic(other, r, c);
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(_cols, _rows);
  for (int r = 0; r < result.Get_rows(); r++) {
    for (int c = 0; c < result.Get_cols(); c++) {
      result._mat[r][c] = _mat[c][r];
    }
  }
  return result;
}

double S21Matrix::dtrTwoTwo() {
  return ((_mat[0][0] * _mat[1][1] - _mat[1][0] * _mat[0][1]));
}

double S21Matrix::dtrThreeThree() {
  return ((_mat[0][0] * (_mat[1][1] * _mat[2][2] - _mat[1][2] * _mat[2][1])) -
          (_mat[0][1] * (_mat[1][0] * _mat[2][2] - _mat[1][2] * _mat[2][0])) +
          (_mat[0][2] * (_mat[1][0] * _mat[2][1] - _mat[1][1] * _mat[2][0])));
}

S21Matrix S21Matrix::cutMatrix(int notR, int notC) {
  S21Matrix newMat((_rows - 1), (_cols - 1));
  int rr = 0, cc = 0;
  for (int r = 0; r < _rows; r++) {
    if (r == notR) continue;
    cc = 0;
    for (int c = 0; c < _cols; c++) {
      if (c == notC) continue;
      newMat._mat[rr][cc] = _mat[r][c];
      cc++;
    }
    rr++;
  }
  return newMat;
}

double S21Matrix::Determinant() {
  double result = 0;
  if (!trueVal(*this, FOR_DTR))
    throw std::range_error(
        "number of columns and rows are not equal \n if r1 == c1 "
        "-> (r1 X c1) = double");
  if (_rows > 3) {
    for (int i = 0; i < _rows; i++) {
      S21Matrix cut(cutMatrix(0, i));
      result += std::pow(-1, i) * _mat[0][i] * cut.Determinant();
    }
  }
  if (_rows == 3) {
    result = dtrThreeThree();
  }
  if (_rows == 2) {
    result = dtrTwoTwo();
  }
  if (_rows == 1) {
    result = _mat[0][0];
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!trueVal(*this, FOR_DTR))
    throw std::range_error(
        "number of columns and rows are not equal \n if r1 == c1 "
        "-> (r1 X c1)");
  S21Matrix result(_rows, _cols);
  if (_rows == 1)
    result = *this;
  else
    for (int r = 0; r < result._rows; r++) {
      for (int c = 0; c < result._cols; c++) {
        S21Matrix cut(cutMatrix(r, c));
        result._mat[r][c] = std::pow(-1, r + c) * cut.Determinant();
      }
    }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (!trueVal(*this, FOR_DTR)) {
    throw std::range_error(
        "number of columns and rows are not equal \n if r1 == c1 "
        "-> (r1 X c1)");
  }
  S21Matrix someMat = *this;
  double det = someMat.Determinant();
  if (det == 0)
    throw std::range_error(
        "the determinant of the matrix is ​​0 \n if (r1 X c1) => DET != 0 "
        "-> (r1 X c1)");
  if (_rows != 1) {
    *this = CalcComplements();
    *this = Transpose();
    MulNumber(((double)1 / det));
  } else {
    MulNumber(((double)1 / det));
  }
  return *this;
}