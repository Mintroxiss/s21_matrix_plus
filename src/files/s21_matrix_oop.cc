#include "../include/s21_matrix_oop.h"

S21Matrix::S21Matrix(int rows, int cols) {
  CheckingMatrixRowsCols(rows, cols);
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) matrix_[i][j] = 0;
  }
}

S21Matrix::S21Matrix() : S21Matrix(2, 2) {}

S21Matrix::S21Matrix(const S21Matrix &other) {
  matrix_ = nullptr;
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  other.rows_ = 0;
  cols_ = other.cols_;
  other.cols_ = 0;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  MemoryFree();
  rows_ = 0;
  cols_ = 0;
}

int S21Matrix::GetRows() { return rows_; }

void S21Matrix::SetRows(int rows) {
  CheckingMatrixRowsCols(rows, cols_);
  if (rows_ != rows) {
    double **new_matrix = new double *[rows];
    for (int i = 0; i < rows; i++) {
      new_matrix[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) new_matrix[i][j] = 0;
    }
    for (int i = 0; i < (rows_ < rows ? rows_ : rows); i++)
      for (int j = 0; j < cols_; j++) new_matrix[i][j] = matrix_[i][j];
    MemoryFree();
    matrix_ = new_matrix;
    new_matrix = nullptr;
    rows_ = rows;
  }
}

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetCols(int cols) {
  CheckingMatrixRowsCols(rows_, cols);
  if (cols_ != cols) {
    double **new_matrix = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      new_matrix[i] = new double[cols];
      for (int j = 0; j < cols; j++) new_matrix[i][j] = 0;
    }
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < (cols_ < cols ? cols_ : cols); j++)
        new_matrix[i][j] = matrix_[i][j];
    MemoryFree();
    matrix_ = new_matrix;
    new_matrix = nullptr;
    cols_ = cols;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  } else {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) return false;
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  CheckingSize(other);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  CheckingSize(other);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  CheckingMulMatrix(other);
  S21Matrix result{rows_, other.cols_};
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      for (int k = 0; k < cols_; k++)
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
  CopyMatrix(result);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result{cols_, rows_};
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) result.matrix_[j][i] = matrix_[i][j];
  return result;
}

double S21Matrix::Determinant() {
  CheckingSquare();
  S21Matrix copy{*this};
  double det = 1.0;
  for (int i = 0; i < copy.rows_; ++i) {
    // Находим максимальный элемент в текущем  столбце
    double mx = fabs(copy.matrix_[i][i]);
    int id_x = i;
    for (int j = i + 1; j < copy.cols_; ++j) {
      if (mx < fabs(copy.matrix_[i][j])) {
        mx = fabs(copy.matrix_[i][id_x = j]);
      }
    }
    // Переставляем строки если нужно
    if (id_x != i) {
      for (int j = i; j < copy.rows_; ++j) {
        double t = copy.matrix_[j][i];
        copy.matrix_[j][i] = copy.matrix_[j][id_x];
        copy.matrix_[j][id_x] = t;
      }
      det = -det;
    }
    // Обнуляем элементы ниже главной диагонали
    for (int k = i + 1; k < copy.rows_; ++k) {
      double t = copy.matrix_[k][i] / copy.matrix_[i][i];
      for (int j = i; j < copy.cols_; ++j) {
        copy.matrix_[k][j] -= copy.matrix_[i][j] * t;
      }
    }
  }
  for (int i = 0; i < copy.rows_; ++i) {
    det *= copy.matrix_[i][i];
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  CheckingSquare();
  CheckingMinorSize();
  S21Matrix result{rows_, cols_};
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double value = CountMatrixComplementsElement(i, j);
      result.matrix_[i][j] = pow(-1, (i + 1) + (j + 1)) * value;
    }
  }
  return result;
}

double S21Matrix::CountMatrixComplementsElement(int index_cross_out_row,
                                                int index_cross_out_column) {
  S21Matrix matrix_minor{rows_ - 1, cols_ - 1};
  int minor_i = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != index_cross_out_row) {
      int minor_j = 0;
      for (int j = 0; j < cols_; j++) {
        if (j != index_cross_out_column) {
          matrix_minor.matrix_[minor_i][minor_j] = matrix_[i][j];
          minor_j++;
        }
      }
      minor_i++;
    }
  }
  return matrix_minor.Determinant();
}

S21Matrix S21Matrix::InverseMatrix() {
  CheckingUnzeroDet();
  S21Matrix result{CalcComplements().Transpose()};
  result.MulNumber(1.0 / Determinant());
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix copy{*this};
  copy.SumMatrix(other);
  return copy;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix copy{*this};
  copy.SubMatrix(other);
  return copy;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix copy{*this};
  copy.MulMatrix(other);
  return copy;
}

S21Matrix S21Matrix::operator*(double value) {
  S21Matrix copy{*this};
  copy.MulNumber(value);
  return copy;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  CopyMatrix(other);
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

S21Matrix &S21Matrix::operator*=(double value) {
  MulNumber(value);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  CheckingBounds(i, j);
  return matrix_[i][j];
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  MemoryFree();
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }
}

void S21Matrix::MemoryFree() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
  }
}

void S21Matrix::CheckingUnzeroDet() {
  if (Determinant() == 0.0)
    throw std::length_error("Определитель матрицы равен 0");
}

void S21Matrix::CheckingSquare() {
  if (rows_ != cols_) throw std::length_error("Матрица не является квадратной");
}

void S21Matrix::CheckingMulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::length_error(
        "Число столбцов первой матрицы не равно числу строк второй матрицы");
}

void S21Matrix::CheckingSize(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::length_error("Различная размерность матриц");
}

void S21Matrix::CheckingMatrixRowsCols(int rows, int cols) {
  if (rows < 1 || cols < 1)
    throw std::length_error("Невозможная размерность матрицы");
}

void S21Matrix::CheckingBounds(int i, int j) {
  if (i > rows_ || i < 0 || j > cols_ || j < 0)
    throw std::length_error("Индекс за границами матрицы");
}

void S21Matrix::CheckingMinorSize() {
  if (rows_ == 1 && cols_ == 1)
    throw std::length_error("Матрица 1x1 не имеет матрицы алгебр. доп.");
}