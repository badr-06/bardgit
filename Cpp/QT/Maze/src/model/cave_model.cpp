#include "cave_model.h"

#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <ctime>

void CaveModel::resize(int rows, int columns) {
  rows_ = rows;
  columns_ = columns;
  matrix_.assign(rows, std::vector<int>(columns, 0));
}

void CaveModel::init() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      matrix_[i][j] = 0;
    }
  }
}

bool CaveModel::generationBool() { return (std::rand() % 100) >= 50; }

bool CaveModel::loadFromFile(const QString& filename) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }

  QTextStream in(&file);
  int rows = 0;
  int columns = 0;
  in >> rows >> columns;
  if (in.status() != QTextStream::Ok || rows <= 0 || columns <= 0 ||
      rows > kMaxSize || columns > kMaxSize) {
    return false;
  }

  resize(rows, columns);
  init();

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      in >> matrix_[i][j];
      if (in.status() != QTextStream::Ok) {
        return false;
      }
    }
  }

  return true;
}

void CaveModel::generate(int rows, int columns) {
  resize(rows, columns);
  init();

  std::srand(static_cast<unsigned>(std::time(nullptr)));

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      if (generationBool()) {
        matrix_[i][j] = 1;
      }
    }
  }
}

int CaveModel::countNeighbors(int x, int y) const {
  int count = 0;

  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      const int xi = x + i;
      const int yj = y + j;
      if (x == xi && y == yj) continue;

      if (xi >= 0 && yj >= 0 && xi < rows_ && yj < columns_) {
        if (matrix_[xi][yj]) {
          ++count;
        }
      } else {
        ++count;
      }
    }
  }

  return count;
}

void CaveModel::updateState() {
  std::vector<std::vector<int>> next(rows_, std::vector<int>(columns_, 0));

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      const int count = countNeighbors(i, j);
      if (matrix_[i][j]) {
        next[i][j] = count < death_limit_ ? 0 : 1;
      } else {
        next[i][j] = count > birth_limit_ ? 1 : 0;
      }
    }
  }

  matrix_ = std::move(next);
}
