#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

  // Находит элемент матрицы алгебраических дополнений
  double CountMatrixComplementsElement(int index_cross_out_row,
                                       int index_cross_out_column);

  // Копирует матрицу в текущую
  void CopyMatrix(const S21Matrix &other);

  // Освобождает память, выделенную под matrix_
  void MemoryFree();

  // Сверяет размерности матриц
  void CheckingSize(const S21Matrix &other);

  // Проверяет условие для возможности переменожения матриц
  void CheckingMulMatrix(const S21Matrix &other);

  // Проверяет, является ли матрица квадратной
  void CheckingSquare();

  // Проверяет детерминант на нулевое значение
  void CheckingUnzeroDet();

  // Проверяет корректность размерности матрицы
  void CheckingMatrixRowsCols(int rows, int cols);

  // Проверяет индексы на приемлимость
  void CheckingBounds(int i, int j);

  // Проверяет размерность для создания матрицы алгебраических дополнений
  void CheckingMinorSize();

 public:
  // Параметризированный конструктор
  S21Matrix(int rows, int cols);

  // Базовый конструктор
  S21Matrix();

  // Конструктор копирования
  S21Matrix(const S21Matrix &other);

  // Конструктор переноса
  S21Matrix(S21Matrix &&other);

  // Деструктор
  ~S21Matrix();

  int GetRows();
  void SetRows(int rows);

  int GetCols();
  void SetCols(int cols);

  // Проверяет матрицы на равенство между собой. true - равны, false - нет
  bool EqMatrix(const S21Matrix &other);

  // Прибавляет вторую матрицу к текущей
  void SumMatrix(const S21Matrix &other);

  // Вычитает из текущей матрицы другую
  void SubMatrix(const S21Matrix &other);

  // Умножает текущую матрицу на число
  void MulNumber(const double num);

  // Умножает текущую матрицу на вторую
  void MulMatrix(const S21Matrix &other);

  // Создает новую транспонированную матрицу из текущей и возвращает её
  S21Matrix Transpose();

  // Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает её
  S21Matrix CalcComplements();

  // Вычисляет и возвращает определитель текущей матрицы
  double Determinant();

  // Вычисляет и возвращает обратную матрицу
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double value);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double value);
  double &operator()(int i, int j);
};

#endif  // S21_MATRIX_OOP_H_
