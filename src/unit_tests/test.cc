#include <gtest/gtest.h>

#include "../include/s21_matrix_oop.h"

TEST(test, DefaultConstructorTest1) {
  S21Matrix mat;
  ASSERT_EQ(mat.GetRows(), 2);
  ASSERT_EQ(mat.GetCols(), 2);
}

TEST(S21MatrixTest, ParamConstructorTest1) {
  ASSERT_NO_THROW(S21Matrix matrix(5, 5));
}

TEST(S21MatrixTest, CopyConstructorTest1) {
  S21Matrix a(5, 5);
  S21Matrix b(a);
  ASSERT_EQ(a.GetRows(), b.GetRows());
  ASSERT_EQ(a.GetCols(), b.GetCols());
  ASSERT_NO_THROW(S21Matrix b(a));
}

TEST(S21MatrixTest, CopyConstructorTest2) {
  S21Matrix A(3, 4);
  S21Matrix B(A);
  EXPECT_EQ(3, B.GetRows());
  EXPECT_EQ(4, B.GetCols());
  EXPECT_EQ(1, A == B);
}

TEST(S21MatrixTest, EqMatrixTest1) {
  S21Matrix a;
  S21Matrix b;

  bool result1 = a.EqMatrix(b);
  bool result2 = b.EqMatrix(a);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(result2 = result1);
}

TEST(S21MatrixTest, EqMatrixTest2) {
  S21Matrix a(2, 1);
  S21Matrix b(1, 1);

  bool result1 = a.EqMatrix(b);
  bool result2 = b.EqMatrix(a);
  EXPECT_FALSE(result1);
  EXPECT_FALSE(result2);
  EXPECT_FALSE(result2 = result1);
}

TEST(S21MatrixTest, EqMatrixTest3) {
  S21Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;

  S21Matrix matrix(3, 3);
  matrix(0, 0) = 14, matrix(0, 1) = 16, matrix(0, 2) = 6;
  matrix(1, 0) = 10, matrix(1, 1) = 18, matrix(1, 2) = 2;
  matrix(2, 0) = 18, matrix(2, 1) = 8, matrix(2, 2) = 4;

  EXPECT_FALSE(A.EqMatrix(matrix));
}

TEST(S21MatrixTest, EqMatrixTest4) {
  S21Matrix A(3, 3);
  A(0, 0) = 5555555555, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;

  S21Matrix matrix(3, 3);
  matrix(0, 0) = 5555555555, matrix(0, 1) = 8, matrix(0, 2) = 3;
  matrix(1, 0) = 5, matrix(1, 1) = 9, matrix(1, 2) = 1;
  matrix(2, 0) = 9, matrix(2, 1) = 4, matrix(2, 2) = 2;

  EXPECT_TRUE(A.EqMatrix(matrix));
}

TEST(S21MatrixTest, SumMatrixTest1) {
  S21Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 14, matrix(0, 1) = 16, matrix(0, 2) = 6;
  matrix(1, 0) = 10, matrix(1, 1) = 18, matrix(1, 2) = 2;
  matrix(2, 0) = 18, matrix(2, 1) = 8, matrix(2, 2) = 4;
  A.SumMatrix(A);
  ASSERT_EQ(true, A.EqMatrix(matrix));
}

TEST(S21MatrixTest, SumMatrixTest2) {
  S21Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;
  S21Matrix matrix(3, 4);
  matrix(0, 0) = 14, matrix(0, 1) = 16, matrix(0, 2) = 6;
  matrix(1, 0) = 10, matrix(1, 1) = 18, matrix(1, 2) = 2;
  matrix(2, 0) = 18, matrix(2, 1) = 8, matrix(2, 2) = 4;

  ASSERT_ANY_THROW(A.SumMatrix(matrix));
}

TEST(S21MatrixTest, SumMatrixTest3) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  expected(0, 0) = 6;
  expected(0, 1) = 8;
  expected(1, 0) = 10;
  expected(1, 1) = 12;

  a.SumMatrix(b);
  EXPECT_TRUE(a == expected);
}

TEST(S21MatrixTest, SumMatrixTest4) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  expected(0, 0) = 6;
  expected(0, 1) = 8;
  expected(1, 0) = 10;
  expected(1, 1) = 12;

  a += b;
  EXPECT_TRUE(a == expected);
}

TEST(S21MatrixTest, SubMatrixTest1) {
  S21Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 0, matrix(0, 1) = 0, matrix(0, 2) = 0;
  matrix(1, 0) = 0, matrix(1, 1) = 0, matrix(1, 2) = 0;
  matrix(2, 0) = 0, matrix(2, 1) = 0, matrix(2, 2) = 0;
  A.SubMatrix(A);
  ASSERT_EQ(true, A.EqMatrix(matrix));
}

TEST(S21MatrixTest, MulMatrixTest1) {
  S21Matrix A(3, 3);
  S21Matrix B(1, 1);

  EXPECT_THROW(A.MulMatrix(B), std::length_error);
}

TEST(S21MatrixTest, MulNumberTest1) {
  const double num = 2;
  S21Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 14, matrix(0, 1) = 16, matrix(0, 2) = 6;
  matrix(1, 0) = 10, matrix(1, 1) = 18, matrix(1, 2) = 2;
  matrix(2, 0) = 18, matrix(2, 1) = 8, matrix(2, 2) = 4;
  A.MulNumber(num);
  EXPECT_TRUE(A == matrix);
}

TEST(S21MatrixTest, MulNumberTest2) {
  const double num = 5;
  S21Matrix A(3, 3);
  A(0, 0) = 7, A(0, 1) = 8, A(0, 2) = 3;
  A(1, 0) = 5, A(1, 1) = 9, A(1, 2) = 1;
  A(2, 0) = 9, A(2, 1) = 4, A(2, 2) = 2;
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 35, matrix(0, 1) = 40, matrix(0, 2) = 15;
  matrix(1, 0) = 25, matrix(1, 1) = 45, matrix(1, 2) = 5;
  matrix(2, 0) = 45, matrix(2, 1) = 20, matrix(2, 2) = 10;
  A.MulNumber(num);
  EXPECT_TRUE(A == matrix);
}

TEST(S21MatrixTest, MulNumberTest3) {
  S21Matrix a(2, 2);
  S21Matrix expected(2, 2);
  const double num = 3;
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  expected(0, 0) = 3;
  expected(0, 1) = 6;
  expected(1, 0) = 9;
  expected(1, 1) = 12;

  a.MulNumber(num);
  EXPECT_TRUE(a == expected);
}

TEST(S21MatrixTest, MulMatrixTest2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  expected(0, 0) = 19;
  expected(0, 1) = 22;
  expected(1, 0) = 43;
  expected(1, 1) = 50;

  a.MulMatrix(b);
  EXPECT_TRUE(a == expected);
}

TEST(S21MatrixTest, DeterminantTest1) {
  S21Matrix test_matrix(2, 3);
  S21Matrix matrix_before = test_matrix;

  EXPECT_ANY_THROW(test_matrix.Determinant());
  EXPECT_TRUE(test_matrix == matrix_before);
}
TEST(S21MatrixTest, DeterminantTest2) {
  S21Matrix A(1, 2);
  EXPECT_THROW(A.Determinant(), std::length_error);
}

TEST(S21MatrixTest, DeterminantTest3) {
  S21Matrix A(3, 3);
  A(0, 0) = 0, A(0, 1) = 1, A(0, 2) = 2;
  A(1, 0) = 3, A(1, 1) = 4, A(1, 2) = 5;
  A(2, 0) = 6, A(2, 1) = 0, A(2, 2) = 7;

  double res = A.Determinant();
  EXPECT_TRUE(-39.0 == res);
}

TEST(S21MatrixTest, DeterminantTest4) {
  S21Matrix A(3, 3);
  A(0, 0) = 6, A(0, 1) = 0, A(0, 2) = 7;
  A(1, 0) = 3, A(1, 1) = 4, A(1, 2) = 5;
  A(2, 0) = 0, A(2, 1) = 1, A(2, 2) = 2;

  double res = A.Determinant();
  EXPECT_TRUE(39.0 == res);
}

TEST(S21MatrixTest, DeterminantTest5) {
  S21Matrix A(1, 1);

  double res = A.Determinant();
  EXPECT_TRUE(0.0 == res);
}

TEST(S21MatrixTest, DeterminantTest6) {
  S21Matrix A(1, 2);
  EXPECT_THROW(A.Determinant(), std::length_error);
}

TEST(S21MatrixTest, CalcComplementsTest1) {
  S21Matrix A(3, 2);
  EXPECT_THROW(A.CalcComplements(), std::length_error);
}

TEST(S21MatrixTest, CalcComplementsTest2) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 3);

  EXPECT_THROW(A.SubMatrix(B), std::length_error);
}

TEST(S21MatrixTest, CalcComplementsTest3) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 0;
  m1(1, 1) = 4;
  m1(1, 2) = 2;
  m1(2, 0) = 5;
  m1(2, 1) = 2;
  m1(2, 2) = 1;

  m2(0, 0) = 0;
  m2(0, 1) = 10;
  m2(0, 2) = -20;
  m2(1, 0) = 4;
  m2(1, 1) = -14;
  m2(1, 2) = 8;
  m2(2, 0) = -8;
  m2(2, 1) = -2;
  m2(2, 2) = 4;

  bool res = m1.CalcComplements() == m2;

  EXPECT_EQ(res, true);
}

TEST(S21MatrixTest, OperatorSumTest) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;
  A = B + B;

  S21Matrix res(3, 4);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(0, 3) = 8;
  res(1, 0) = 10;
  res(1, 1) = 12;
  res(1, 2) = 14;
  res(1, 3) = 16;
  res(2, 0) = 18;
  res(2, 1) = 20;
  res(2, 2) = 22;
  res(2, 3) = 24;

  EXPECT_EQ(1, A == res);
};

TEST(S21MatrixTest, OperatorSubTest) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  S21Matrix C(3, 4);

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;

  A = B - B;

  EXPECT_EQ(1, A == C);
}

TEST(S21MatrixTest, OperatorMulTest) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 1;

  B(1, 0) = 1;
  B(1, 1) = 1;
  A = B * B;
  EXPECT_EQ(1, A == B);
}

TEST(S21MatrixTest, OperatorMulNumberTest) {
  S21Matrix A(2, 2);
  S21Matrix res(2, 2);
  double num = 5;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  res(0, 0) = 5;
  res(0, 1) = 10;
  res(1, 0) = 25;
  res(1, 1) = 30;

  A = A * num;
  EXPECT_TRUE(A == res);
}

TEST(S21MatrixTest, OperatorMulNumberEqTest) {
  S21Matrix A(2, 2);
  S21Matrix res(2, 2);
  double num = 5;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  res(0, 0) = 5;
  res(0, 1) = 10;
  res(1, 0) = 25;
  res(1, 1) = 30;

  A *= num;
  EXPECT_TRUE(A == res);
}

TEST(S21MatrixTest, OperatorErrorTest) {
  S21Matrix B(2, 2);
  EXPECT_THROW((B(0, 5) = 2), std::length_error);
}

TEST(S21MatrixTest, OperatorErrorTest1) {
  S21Matrix B(3, 3);
  EXPECT_THROW((B(4, 1) = 1), std::length_error);
}

TEST(S21MatrixTest, OperatorSubReqTest1) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix res(2, 2);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  res(0, 0) = 2;
  res(0, 1) = 4;
  res(1, 0) = 10;
  res(1, 1) = 12;

  A += B;
  EXPECT_TRUE(A == res);
}

TEST(S21MatrixTest, OperatorSubTest1) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix res(2, 2);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  res(0, 0) = 0;
  res(0, 1) = 0;
  res(1, 0) = 0;
  res(1, 1) = 0;

  A -= B;
  EXPECT_TRUE(A == res);
}

TEST(S21MatrixTest, OperatorMulTest1) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix res(2, 2);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  res(0, 0) = 11;
  res(0, 1) = 14;
  res(1, 0) = 35;
  res(1, 1) = 46;

  A *= B;
  EXPECT_TRUE(A == res);
}

TEST(S21MatrixTest, OperatorSumNumberTest1) {
  S21Matrix A(2, 2);
  S21Matrix res(2, 2);
  double num = 5;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  res(0, 0) = 5;
  res(0, 1) = 10;
  res(1, 0) = 25;
  res(1, 1) = 30;

  A *= num;
  EXPECT_TRUE(A == res);
}

TEST(S21MatrixTest, InverseMatrixTest1) {
  S21Matrix A(1, 2);
  EXPECT_THROW(A.InverseMatrix(), std::length_error);
}

TEST(S21MatrixTest, InverseMatrixTest3) {
  S21Matrix A(1, 1);
  EXPECT_THROW(A.InverseMatrix(), std::length_error);
}

TEST(S21MatrixTest, InverseTest2) {
  S21Matrix A(2, 2);
  S21Matrix res(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  res(0, 0) = -2;
  res(0, 1) = 1;
  res(1, 0) = 1.5;
  res(1, 1) = -0.5;

  EXPECT_TRUE(A.InverseMatrix() == res);
}

TEST(S21MatrixTest, TransposeTest1) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  EXPECT_TRUE(A.Transpose() == B);
}

TEST(S21MatrixTest, setTest) {
  S21Matrix a(2, 2);
  S21Matrix b(4, 4);
  a.SetCols(4);
  a.SetRows(4);
  EXPECT_TRUE(a == b);
}

TEST(S21MatrixTest, ConstructorMoveTest) {
  S21Matrix A(5, 5);
  S21Matrix B(std::move(A));
  EXPECT_EQ(5, B.GetRows());
  EXPECT_EQ(5, B.GetCols());
  EXPECT_EQ(0, A.GetRows());
  EXPECT_EQ(0, A.GetCols());
}

TEST(S21MatrixTest, ErrorTest1) {
  EXPECT_THROW(S21Matrix B(0, 4), std::length_error);
}

TEST(S21MatrixTest, ErrorTest2) {
  S21Matrix B(1, 1);
  B(0, 0) = 4;
  EXPECT_THROW(B.CalcComplements(), std::length_error);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
