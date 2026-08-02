#include "maze_model.h"

#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <ctime>

void MazeModel::resize(int rows, int columns) {
  rows_ = rows;
  columns_ = columns;
  matrix1_.assign(rows, std::vector<int>(columns, 0));
  matrix2_.assign(rows, std::vector<int>(columns, 0));
  matrix3_.assign(rows, std::vector<int>(columns, 0));
}

void MazeModel::init() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      matrix1_[i][j] = 0;
      matrix2_[i][j] = 0;
      matrix3_[i][j] = 0;
    }
  }
}

bool MazeModel::loadFromFile(const QString& filename) {
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
      in >> matrix1_[i][j];
      if (in.status() != QTextStream::Ok) {
        return false;
      }
    }
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      in >> matrix2_[i][j];
      if (in.status() != QTextStream::Ok) {
        return false;
      }
    }
  }

  return true;
}

bool MazeModel::saveToFile(const QString& filename) const {
  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    return false;
  }

  QTextStream out(&file);
  out << rows_ << " " << columns_ << "\n";

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      out << matrix1_[i][j] << " ";
    }
    out << "\n";
  }
  out << "\n";

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      out << matrix2_[i][j] << " ";
    }
    out << "\n";
  }

  return true;
}

bool MazeModel::generationBool() { return (std::rand() % 100) >= 50; }

void MazeModel::mergeSets(std::vector<int>& matrix, int a, int b) {
  const int from = matrix[b];
  const int to = matrix[a];
  for (int i = 0; i < columns_; ++i) {
    if (matrix[i] == from) {
      matrix[i] = to;
    }
  }
}

void MazeModel::checkLowerBounds(int i, std::vector<int>& matrix) {
  for (int j = 0; j < columns_;) {
    bool flag = true;
    bool check_low_b = false;
    const int num = matrix[j];
    int end = 0;
    int start = j;

    while (flag) {
      if ((j >= columns_ - 1) || ((j < columns_ - 1) && matrix[j + 1] != num)) {
        flag = false;
        end = j;
      }
      if (matrix2_[i][j] == 0) {
        check_low_b = true;
      }
      ++j;
    }

    if (!check_low_b) {
      if ((end - start) == 0) {
        matrix2_[i][end] = 0;
      } else {
        const int idx = (std::rand() % (end - start + 1)) + start;
        matrix2_[i][idx] = 0;
      }
    }
  }
}

void MazeModel::generate(int rows, int columns) {
  resize(rows, columns);
  init();

  std::srand(static_cast<unsigned>(std::time(nullptr)));

  std::vector<int> matrix(columns, 0);
  int counter = 1;

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      if (!matrix[j]) {
        matrix[j] = counter++;
      }
    }

    for (int j = 0; j < columns_; ++j) {
      if (j < (columns_ - 1) && matrix[j] == matrix[j + 1]) {
        matrix1_[i][j] = 1;
      } else if (generationBool()) {
        matrix1_[i][j] = 1;
      } else if (j < (columns_ - 1)) {
        mergeSets(matrix, j, j + 1);
      }
    }

    for (int j = 0; j < columns_; ++j) {
      if ((j == 0 && matrix[j] != matrix[j + 1]) ||
          (j == columns_ - 1 && matrix[j] != matrix[j - 1]) ||
          ((j > 0 && j < columns_ - 1) && (matrix[j - 1] != matrix[j] &&
                                           matrix[j] != matrix[j + 1]))) {
        matrix2_[i][j] = 0;
      } else if (generationBool()) {
        matrix2_[i][j] = 1;
      }
    }

    if (i < (rows_ - 1)) {
      checkLowerBounds(i, matrix);
      for (int j = 0; j < columns_; ++j) {
        if (matrix2_[i][j] == 1) {
          matrix[j] = 0;
        }
      }
    } else {
      for (int j = 0; j < columns_ - 1; ++j) {
        if (matrix[j] != matrix[j + 1]) {
          matrix1_[i][j] = 0;
          mergeSets(matrix, j, j + 1);
        }
      }
    }
  }
}

void MazeModel::clearSolution() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      matrix3_[i][j] = 0;
    }
  }
}

bool MazeModel::dfs(std::vector<std::vector<bool>>& visit, Point current,
                    Point end, std::vector<Point>& path) {
  if (visit[current.y][current.x]) {
    return false;
  }

  visit[current.y][current.x] = true;
  path.push_back(current);

  if (current.x == end.x && current.y == end.y) {
    return true;
  }

  const int dx[] = {1, 0, -1, 0};
  const int dy[] = {0, 1, 0, -1};

  for (int i = 0; i < 4; ++i) {
    const int ny = current.y + dy[i];
    const int nx = current.x + dx[i];

    if (ny < 0 || ny >= rows_ || nx < 0 || nx >= columns_) {
      continue;
    }

    if (matrix1_[current.y][current.x] && dx[i] == 1) continue;
    if (matrix2_[current.y][current.x] && dy[i] == 1) continue;
    if (matrix1_[current.y][current.x - 1] && dx[i] == -1) continue;
    if (matrix2_[current.y - 1][current.x] && dy[i] == -1) continue;

    if (dfs(visit, {ny, nx}, end, path)) {
      return true;
    }
  }

  path.pop_back();
  return false;
}

bool MazeModel::solve(int y1, int x1, int y2, int x2) {
  clearSolution();

  std::vector<std::vector<bool>> visit(rows_, std::vector<bool>(columns_, false));
  std::vector<Point> path;
  path.reserve(rows_ * columns_);

  if (dfs(visit, {y1, x1}, {y2, x2}, path)) {
    for (const Point& p : path) {
      matrix3_[p.y][p.x] = 1;
    }
    return true;
  }

  return false;
}
