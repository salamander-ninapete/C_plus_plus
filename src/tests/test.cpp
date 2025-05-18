#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(S21MatrixTest, SumMatrixTest1) {
  S21Matrix A(1, 1);
  A(0, 0) = 1.0;
  S21Matrix B(1, 1);
  B(0, 0) = 2.0;
  S21Matrix result(1, 1);
  A.SumMatrix(B);
  result(0, 0) = 3.0;
  EXPECT_TRUE(A.EqMatrix(result));
}

TEST(S21MatrixTest, SumMatrixTest2) {
  S21Matrix A;
  A(0, 0) = 1.0;
  S21Matrix B;
  B(0, 0) = 2.0;
  S21Matrix result;
  A.SumMatrix(B);
  result(0, 0) = 3.0;
  EXPECT_TRUE(A.EqMatrix(result));
}

TEST(S21MatrixTest, SumMatrixTest3) {
  S21Matrix A(2, 3);
  A(0, 0) = 1.0;
  S21Matrix B(2, 2);
  B(0, 0) = 2.0;
  EXPECT_THROW(A.SumMatrix(B), std::range_error);
}

TEST(S21MatrixTest, EqMatrix1) {
  S21Matrix A(1, 2);
  S21Matrix B(2, 2);
  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(S21MatrixTest, SubMatrix1) {
  S21Matrix A(2, 3);
  A(0, 0) = 1.0;
  S21Matrix B(2, 2);
  B(0, 0) = 2.0;
  EXPECT_THROW(A.SubMatrix(B), std::range_error);
}

TEST(S21MatrixTest, SubMatrix2) {
  S21Matrix A(2, 2);
  A(0, 0) = 4.0;
  S21Matrix B(2, 2);
  B(0, 0) = 1.0;

  S21Matrix result(2, 2);
  A.SubMatrix(B);
  result(0, 0) = 3.0;
  EXPECT_TRUE(A.EqMatrix(result));
}

TEST(S21MatrixTest, MulNumber1) {
  S21Matrix A(2, 2);
  A(0, 0) = 4.0;
  double B = 3.0;

  S21Matrix result(2, 2);
  A.MulNumber(B);
  result(0, 0) = 12.0;
  EXPECT_TRUE(A.EqMatrix(result));
}

TEST(S21MatrixTest, MulMatrisx1) {
  S21Matrix A(1, 2);
  A(0, 0) = 4.0;
  A(0, 1) = 3.0;

  S21Matrix B(2, 1);
  B(0, 0) = 4.0;
  B(1, 0) = 3.0;

  S21Matrix result(1, 1);
  A.MulMatrix(B);
  result(0, 0) = 25.0;
  EXPECT_TRUE(A.EqMatrix(result));
}

TEST(S21MatrixTest, MulMatrisx2) {
  S21Matrix A(2, 1);
  A(0, 0) = 4.0;
  A(1, 0) = 3.0;

  S21Matrix B(2, 1);
  B(0, 0) = 4.0;
  B(1, 0) = 3.0;

  EXPECT_ANY_THROW(A.MulMatrix(B));
}

TEST(S21MatrixTest, Transpose1) {
  S21Matrix A(1, 2);
  A(0, 0) = 4.0;
  A(0, 1) = 3.0;

  S21Matrix B(2, 1);
  B(0, 0) = 4.0;
  B(1, 0) = 3.0;

  A = A.Transpose();

  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(S21MatrixTest, Determinant1) {
  S21Matrix A(1, 2);
  A(0, 0) = 4.0;
  A(0, 1) = 3.0;

  EXPECT_ANY_THROW(A.Determinant());
}

TEST(S21MatrixTest, Determinant2) {
  S21Matrix A(1, 1);
  A(0, 0) = 5.0;
  double B = 5.0;
  double C = A.Determinant();

  EXPECT_DOUBLE_EQ(C, B);
}

TEST(S21MatrixTest, Determinant3) {
  S21Matrix A(2, 2);
  A(0, 0) = 5.0;
  A(1, 0) = 5.0;

  A(0, 1) = 5.0;
  A(1, 1) = 5.0;
  double B = 0.0;
  double C = A.Determinant();

  EXPECT_DOUBLE_EQ(C, B);
}

TEST(S21MatrixTest, Determinant4) {
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
  double B = 1.0;
  double C = A.Determinant();

  EXPECT_DOUBLE_EQ(C, B);
}

TEST(S21MatrixTest, Determinant5) {
  S21Matrix A(5, 5);
  A(0, 0) = 2.0;
  A(0, 1) = 1.0;
  A(0, 2) = 1.0;
  A(0, 3) = 1.0;
  A(0, 4) = 1.0;

  A(1, 0) = 1.0;
  A(1, 1) = 2.0;
  A(1, 2) = 1.0;
  A(1, 3) = 1.0;
  A(1, 4) = 1.0;

  A(2, 0) = 1.0;
  A(2, 1) = 1.0;
  A(2, 2) = 2.0;
  A(2, 3) = 1.0;
  A(2, 4) = 1.0;

  A(3, 0) = 1.0;
  A(3, 1) = 1.0;
  A(3, 2) = 1.0;
  A(3, 3) = 2.0;
  A(3, 4) = 1.0;

  A(4, 0) = 1.0;
  A(4, 1) = 1.0;
  A(4, 2) = 1.0;
  A(4, 3) = 1.0;
  A(4, 4) = 2.0;

  double B = 6.0;
  double C = A.Determinant();

  EXPECT_DOUBLE_EQ(C, B);
}

TEST(S21MatrixTest, InverseMatrix1) {
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
  B(0, 1) = 18.0;
  B(0, 2) = 5.0;
  B(1, 0) = 20.0;
  B(1, 1) = -15.0;
  B(1, 2) = -4.0;
  B(2, 0) = -5.0;
  B(2, 1) = 4.0;
  B(2, 2) = 1.0;

  S21Matrix C = A.InverseMatrix();

  EXPECT_TRUE(C.EqMatrix(B));
}

TEST(S21MatrixTest, InverseMatrix2) {
  S21Matrix A(3, 1);
  A(0, 0) = 1.0;
  A(1, 0) = 2.0;
  A(2, 0) = 3.0;

  EXPECT_ANY_THROW(A.InverseMatrix());
}

TEST(S21MatrixTest, InverseMatrix3) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;
  A(2, 0) = 7.0;
  A(2, 1) = 8.0;
  A(2, 2) = 9.0;
  EXPECT_ANY_THROW(A.InverseMatrix());
}

TEST(S21MatrixTest, InverseMatrix4) {
  S21Matrix A(1, 1);
  A(0, 0) = 1.0;

  S21Matrix B(1, 1);

  B(0, 0) = 1.0;

  S21Matrix C = A.InverseMatrix();

  EXPECT_TRUE(C.EqMatrix(B));
}

TEST(S21MatrixTest, CalcComplements1) {
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

  EXPECT_TRUE(C.EqMatrix(B));
}

TEST(S21MatrixTest, CalcComplements2) {
  S21Matrix A(3, 1);
  A(0, 0) = 1.0;
  A(1, 0) = 2.0;
  A(2, 0) = 3.0;

  EXPECT_ANY_THROW(A.CalcComplements());
}

TEST(S21MatrixTest, CalcComplements3) {
  S21Matrix A(1, 1);
  A(0, 0) = 5.0;

  S21Matrix B(1, 1);
  B(0, 0) = 5.0;

  S21Matrix C = A.CalcComplements();

  EXPECT_TRUE(C.EqMatrix(B));
}

TEST(MatrixOperatorsTest, add_operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix answer(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  B(0, 0) = 1.0;
  B(0, 1) = 1.0;
  B(1, 0) = 1.0;
  B(1, 1) = 1.0;

  answer(0, 0) = 2.0;
  answer(0, 1) = 3.0;
  answer(1, 0) = 4.0;
  answer(1, 1) = 5.0;

  S21Matrix result = A + B;

  ASSERT_TRUE(result == answer);
}

TEST(MatrixOperatorsTest, sub_operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix answer(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  B(0, 0) = 1.0;
  B(0, 1) = 1.0;
  B(1, 0) = 1.0;
  B(1, 1) = 1.0;

  answer(0, 0) = 0.0;
  answer(0, 1) = 1.0;
  answer(1, 0) = 2.0;
  answer(1, 1) = 3.0;

  S21Matrix result = A - B;

  ASSERT_TRUE(result == answer);
}

TEST(MatrixOperatorsTest, multiply_matrix_operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix answer(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  B(0, 0) = 1.0;
  B(0, 1) = 0.0;
  B(1, 0) = 0.0;
  B(1, 1) = 1.0;

  answer(0, 0) = 1.0;
  answer(0, 1) = 2.0;
  answer(1, 0) = 3.0;
  answer(1, 1) = 4.0;

  S21Matrix result = A * B;

  ASSERT_TRUE(result == answer);
}

TEST(MatrixOperatorsTest, multiply_matrix_operator_error) {
  S21Matrix A(1, 1);
  S21Matrix B(2, 1);

  A(0, 0) = 2.0;
  B(0, 0) = 2.0;
  B(1, 0) = 2.0;

  EXPECT_THROW(A * B, std::out_of_range);
}

TEST(MatrixOperatorsTest, multiply_matrix_operator_move) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix answer(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  B(0, 0) = 1.0;
  B(0, 1) = 0.0;
  B(1, 0) = 0.0;
  B(1, 1) = 1.0;

  answer(0, 0) = 1.0;
  answer(0, 1) = 2.0;
  answer(1, 0) = 3.0;
  answer(1, 1) = 4.0;

  S21Matrix result;
  S21Matrix tmp = A * B;
  result = std::move(tmp);

  ASSERT_TRUE(result == answer);
}

TEST(MatrixOperatorsTest, multiply_number_operator) {
  S21Matrix A(2, 2);
  S21Matrix answer(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  answer(0, 0) = 2.0;
  answer(0, 1) = 4.0;
  answer(1, 0) = 6.0;
  answer(1, 1) = 8.0;

  S21Matrix result = A * 2.0;

  ASSERT_TRUE(result == answer);
}

TEST(MatrixOperatorsTest, add_operator_assignment) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix answer(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  B(0, 0) = 1.0;
  B(0, 1) = 1.0;
  B(1, 0) = 1.0;
  B(1, 1) = 1.0;

  answer(0, 0) = 2.0;
  answer(0, 1) = 3.0;
  answer(1, 0) = 4.0;
  answer(1, 1) = 5.0;

  A += B;

  ASSERT_TRUE(A == answer);
}

TEST(MatrixOperatorsTest, subtract_operator_assignment) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix answer(2, 2);

  A(0, 0) = 3.0;
  A(0, 1) = 4.0;
  A(1, 0) = 5.0;
  A(1, 1) = 6.0;

  B(0, 0) = 1.0;
  B(0, 1) = 1.0;
  B(1, 0) = 1.0;
  B(1, 1) = 1.0;

  answer(0, 0) = 2.0;
  answer(0, 1) = 3.0;
  answer(1, 0) = 4.0;
  answer(1, 1) = 5.0;

  A -= B;

  ASSERT_TRUE(A == answer);
}

TEST(MatrixOperatorsTest, multiply_matrix_operator_assignment) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix answer(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  B(0, 0) = 1.0;
  B(0, 1) = 0.0;
  B(1, 0) = 0.0;
  B(1, 1) = 1.0;

  answer(0, 0) = 1.0;
  answer(0, 1) = 2.0;
  answer(1, 0) = 3.0;
  answer(1, 1) = 4.0;

  A *= B;

  ASSERT_TRUE(A == answer);
}

TEST(MatrixOperatorsTest, multiply_number_operator_assignment) {
  S21Matrix A(2, 2);
  S21Matrix answer(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  answer(0, 0) = 2.0;
  answer(0, 1) = 4.0;
  answer(1, 0) = 6.0;
  answer(1, 1) = 8.0;

  A *= 2.0;

  ASSERT_TRUE(A == answer);
}

TEST(MatrixOperatorsTest, assignment_operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  B = A;

  ASSERT_TRUE(B == A);
}

TEST(MatrixOperatorsTest, equality_operator) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;

  ASSERT_TRUE(A == B);
}

TEST(MatrixOperatorsTest, index_operator_error) {
  S21Matrix A(2, 2);

  A(0, 0) = 1.0;
  A(1, 1) = 4.0;

  ASSERT_EQ(A(0, 0), 1.0);
  ASSERT_EQ(A(1, 1), 4.0);

  ASSERT_THROW(A(2, 2), std::out_of_range);
}

TEST(MatrixOperatorsTest, index_operator_correct_const) {
  S21Matrix A(2, 2);

  A(0, 0) = 1.0;
  A(1, 1) = 4.0;

  ASSERT_EQ(A(0, 0), 1.0);
  ASSERT_EQ(A(1, 1), 4.0);

  S21Matrix const B = A;
  ASSERT_EQ(B(1, 1), 4);
}

TEST(MatrixOperatorsTest, const_index_operator_error) {
  S21Matrix A(2, 2);

  A(0, 0) = 1.0;
  A(1, 1) = 4.0;

  ASSERT_EQ(A(0, 0), 1.0);
  ASSERT_EQ(A(1, 1), 4.0);
  const S21Matrix A_const = A;
  ASSERT_THROW(A_const(4, 2), std::out_of_range);
}

TEST(S21MatrixTest, MoveConstructorTest) {
  S21Matrix original(3, 3);
  original(0, 0) = 1.0;
  original(0, 1) = 2.0;
  original(0, 2) = 3.0;
  original(1, 0) = 4.0;
  original(1, 1) = 5.0;
  original(1, 2) = 6.0;
  original(2, 0) = 7.0;
  original(2, 1) = 8.0;
  original(2, 2) = 9.0;

  S21Matrix movedMatrix(std::move(original));

  EXPECT_DOUBLE_EQ(movedMatrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(movedMatrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(movedMatrix(0, 2), 3.0);
  EXPECT_DOUBLE_EQ(movedMatrix(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(movedMatrix(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(movedMatrix(1, 2), 6.0);
  EXPECT_DOUBLE_EQ(movedMatrix(2, 0), 7.0);
  EXPECT_DOUBLE_EQ(movedMatrix(2, 1), 8.0);
  EXPECT_DOUBLE_EQ(movedMatrix(2, 2), 9.0);
}

TEST(S21MatrixTest, SetColsTest1) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;
  A(2, 0) = 7.0;
  A(2, 1) = 8.0;
  A(2, 2) = 9.0;

  A.Set_cols(2);

  EXPECT_EQ(A.Get_rows(), 3);
  EXPECT_EQ(A.Get_cols(), 2);
}

TEST(S21MatrixTest, SetRowsTest1) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;
  A(2, 0) = 7.0;
  A(2, 1) = 8.0;
  A(2, 2) = 9.0;

  A.Set_rows(2);

  EXPECT_EQ(A.Get_rows(), 2);
  EXPECT_EQ(A.Get_cols(), 3);
}

TEST(S21MatrixTest, SetColsTest2) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;
  A(2, 0) = 7.0;
  A(2, 1) = 8.0;
  A(2, 2) = 9.0;

  EXPECT_ANY_THROW(A.Set_cols(0));
}

TEST(S21MatrixTest, SetRowsTest2) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;
  A(2, 0) = 7.0;
  A(2, 1) = 8.0;
  A(2, 2) = 9.0;
  EXPECT_ANY_THROW(A.Set_rows(0));
}

TEST(S21MatrixTest, create_err) { EXPECT_ANY_THROW(S21Matrix A(0, 3)); }

// // Тест для проверки умножения числа на матрицу
// TEST(MatrixTest, Mu) {
//   // Создаем матрицу для тестирования
//   S21Matrix mat(2, 2);
//   mat(0, 0) = 1.0;
//   mat(0, 1) = 2.0;
//   mat(1, 0) = 3.0;
//   mat(1, 1) = 4.0;

//   // Ожидаемая матрица после умножения
//   S21Matrix expected(2, 2);
//   expected(0, 0) = 2.0;
//   expected(0, 1) = 4.0;
//   expected(1, 0) = 6.0;
//   expected(1, 1) = 8.0;

//   // Умножаем число на матрицу
//   S21Matrix result = 2.0 * mat;

//   // Проверяем, что результат совпадает с ожидаемым
//   EXPECT_TRUE(result.EqMatrix(expected));
// }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}